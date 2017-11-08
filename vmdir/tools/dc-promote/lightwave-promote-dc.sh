#!/bin/sh 
#!/bin/sh -x
#
# Script to promote a Photon OS system to a Lightwave Domain Controller
#

#
# Configure these constants to match your environment
# ADMIN_PASSWORD must meet password complexity requirements of vmdir
#                Upper/Lower/Number/Legal punctuation/ 9 < pwd_len <= 20
LIGHTWAVE_AD=10.118.96.62
DC_DOMAIN="lightwave.local"
DC_NAME="photon-addc-test10"
ADMIN_PASSWORD="VMware123@"
PRIV_USER="root"
UNPRIV_USER="abernstein"

LIKEWISE_BASE=/home/abernstein/workspaces/git/lightwave/likewise-open
LIGHTWAVE_BASE=/home/abernstein/workspaces/git/lightwave/lightwave

echo_status()
{
  echo
  echo "$LC: $1"
  LC=$(($LC + 1 ))
}


# ------------------ main ------------------------


# Command line usage: ./lightwave-promote-dc.sh [[IP_PSC]  [Admin PWD]]
#
# Arguments are optional when LIGHTWAVE_AD / ADMIN_PASSWORD variables are set
#
#
# First argument must be IP address of PSC
if [ -n "$1" ]; then
  LIGHTWAVE_AD="$1"
  shift
fi

# Second argument must be Administrator password
if [ -n "$1" ]; then
  ADMIN_PASSWORD="$1"
  shift
fi

# line count "LC" variable for status messages
LC=1

#
#
SCRIPT_DIR=`readlink -f "$0"`
TOOLS_DIR=`dirname $SCRIPT_DIR`
DOMAIN_DN=`echo $DC_DOMAIN | sed -e "s|\.|,dc=|" -e "s|^|dc=|"`
#
#
#
# 0 Sanity tests to validate this script can work at all
if [ -z "$LIGHTWAVE_AD" ]; then
  echo "ERROR: no DC IP address configured"
  exit 1
fi

if [ -z "$ADMIN_PASSWORD" ]; then
  echo "ERROR: Administrator account password not set"
  exit 1
fi

id=`ssh root@$LIGHTWAVE_AD hostname -i`
if [ $? -ne 0 ]; then
  echo "ERROR: 'ssh root@$LIGHTWAVE_AD' failed; fix IP or pub/priv keys"
  exit 1
fi

id=`ssh abernstein@$LIGHTWAVE_AD hostname -i`
if [ $? -ne 0 ]; then
  echo "ERROR: 'ssh abernstein@$LIGHTWAVE_AD' failed; fix IP or pub/priv keys"
  exit 1
fi


fqdn=`ssh abernstein@$LIGHTWAVE_AD hostname -f`
if [ "$fqdn" != "${DC_NAME}.${DC_DOMAIN}" ]; then
  echo "ERROR: Mismatch between promoted domain and local configuration"
  echo "       fix DC_NAME and DC_DOMAIN"
  exit 1
fi

if [ $LIGHTWAVE_AD != $id ]; then
  echo "ERROR: LIGHTWAVE_AD IP address '$LIGHTWAVE_AD' does not match configuration '$id'"
  exit 1
fi

if [ ! -f $LIKEWISE_BASE/release/package/rpm/likewise-open/likewise-open-6.2.11-?.x86_64.rpm  ]; then
  echo "ERROR: file '$LIKEWISE_BASE/likewise-open-6.2.11-?.x86_64.rpm' does not exist"
  exit 1
fi

if [ `ls -1 $LIGHTWAVE_BASE/build/rpmbuild/RPMS/x86_64/*.rpm | wc -l` -eq 0 ]; then
  echo "ERROR '$LIGHTWAVE_BASE/build/rpmbuild/RPMS/x86_64/*.rpm' not found"
  exit 1
fi

# Save Administrator password to a file on AD system
echo -n "$ADMIN_PASSWORD" | ssh root@$LIGHTWAVE_AD 'cat > /var/tmp/promote-pwd.txt'
if [ $? -ne 0 ]; then
  echo "ERROR: Failed setting promote-pwd.txt file on '$LIGHTWAVE_AD' system"
  exit 1
fi

# 1 Copy custom build of Likewise-Open
echo_status "Copy likewise-open to DC"
scp $LIKEWISE_BASE/release/package/rpm/likewise-open/likewise-open-6.2.11-?.x86_64.rpm $LIGHTWAVE_AD:/tmp

# 2 Copy Lightwave --enable-winjoin build
echo_status "Copy lightwave to DC"
scp $LIGHTWAVE_BASE/build/rpmbuild/RPMS/x86_64/*.rpm $LIGHTWAVE_AD:/tmp

# 3 Install Likewise-Open
echo_status "Install likewise-open"
ssh root@$LIGHTWAVE_AD rpm -ivh /tmp/likewise-open-6.2.11-?.x86_64.rpm


# 4 Install Lightwave RPMs
echo_status "Install lightwave"
ssh root@$LIGHTWAVE_AD rpm -ivh /tmp/lightwave-1*.rpm /tmp/lightwave-client-1*.rpm /tmp/lightwave-server-1*.rpm

# 5 Modify /etc/resolv.conf to point to self for DNS
echo_status "Modify /etc/resolv.conf to point to self for DNS"
cat  $TOOLS_DIR/resolv-config.sh | \
  sed -e "s|DC_NAME|$DC_NAME|" -e "s|DC_DOMAIN|$DC_DOMAIN|" -e "s|DOMAIN_DN|$DOMAIN_DN|" > \
  /tmp/resolv-config-edited.sh 
chmod +x /tmp/resolv-config-edited.sh 

echo_status "copy and run resolv-config.sh to domain controller"
scp /tmp/resolv-config-edited.sh abernstein@$LIGHTWAVE_AD:/var/tmp/resolv-config-edited.sh
ssh root@$LIGHTWAVE_AD /var/tmp/resolv-config-edited.sh

# 6 Promote Lightwave PSC
echo_status "Promote Lightwave PSC"
ssh root@$LIGHTWAVE_AD '/opt/vmware/bin/configure-lightwave-server \
  --domain '"$DC_DOMAIN"' --password `cat /var/tmp/promote-pwd.txt`'

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# 6a Fix busted vmafd value DCName value
# Getting localhost vs FQDN of DC
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#
cat <<NNNN | ssh root@$LIGHTWAVE_AD cat > /tmp/regshell-vmafd.sh
/opt/likewise/bin/lwregshell set_value   '[HKEY_THIS_MACHINE\\Services\\vmafd\\Parameters]' DCName "`ssh root@$LIGHTWAVE_AD hostname -f`" > /dev/null 2>&1
if [ \$? -ne 0 ]; then
  /opt/likewise/bin/lwregshell add_value   '[HKEY_THIS_MACHINE\\Services\\vmafd\\Parameters]' DCName REG_SZ "`ssh root@$LIGHTWAVE_AD hostname -f`"
fi
NNNN
scp /tmp/regshell-vmafd.sh root@$LIGHTWAVE_AD:/tmp
ssh root@$LIGHTWAVE_AD sh /tmp/regshell-vmafd.sh

# 7 Start Likewise SMB services
ssh root@$LIGHTWAVE_AD '( /opt/likewise/bin/lwsm start npfs && /opt/likewise/bin/lwsm start pvfs && 
    /opt/likewise/bin/lwsm start rdr && /opt/likewise/bin/lwsm start srv )'

# 8 Modify IP tables entries
ssh root@$LIGHTWAVE_AD '( iptables -I INPUT --proto icmp -j ACCEPT &&
    iptables -I INPUT --proto udp --dport 389 -j ACCEPT &&
    iptables -I INPUT --proto tcp --dport 445 -j ACCEPT &&
    iptables -I INPUT --proto tcp --dport 139 -j ACCEPT &&
    iptables -I INPUT --proto tcp --dport 389 -j ACCEPT &&
    iptables -I OUTPUT --proto tcp --dport 389 -j ACCEPT )'

## 9 Add DNS forwarder
## Don't do this. Forwarder support is broken. Preserving 2nd/3rd entries in 
## resolv.conf accomplishes the same thing.
#ssh root@$LIGHTWAVE_AD '/opt/vmware/bin/vmdns-cli add-forwarder 10.155.23.1 \
#    --server localhost --username Administrator --domain "$DC_DOMAIN" --password `cat /var/tmp/promote-pwd.txt`'
#

# 10 Additional DNS SRV records:
echo_status "DNS kerberos-master SRV tcp record"
ssh root@$LIGHTWAVE_AD \
  '/opt/vmware/bin/vmdns-cli add-record --zone '"$DC_DOMAIN"' \
   --type SRV \
   --service kerberos-master \
   --protocol tcp \
   --target '"$DC_NAME"' \
   --priority 1 \
   --weight 1 \
   --port 88 \
   --server localhost \
   --password `cat /var/tmp/promote-pwd.txt`'

echo_status "DNS kerberos-master SRV udp record"
ssh root@$LIGHTWAVE_AD \
  '/opt/vmware/bin/vmdns-cli add-record --zone '"$DC_DOMAIN"' \
   --type SRV \
   --service kerberos-master \
   --protocol udp \
   --target '"$DC_NAME"' \
   --priority 1 \
   --weight 1 \
   --port 88 \
   --server localhost \
   --password `cat /var/tmp/promote-pwd.txt`'

echo_status "DNS _ldap._tcp.Default-First-Site-Name._sites.dc._msdcs SRV tcp record"
ssh root@$LIGHTWAVE_AD \
  '/opt/vmware/bin/vmdns-cli add-record --zone '"$DC_DOMAIN"' \
   --type SRVFF \
   --service-literal  _ldap._tcp.Default-First-Site-Name._sites.dc._msdcs \
   --protocol tcp \
   --target '"$DC_NAME"' \
   --priority 1 \
   --weight 1 \
   --port 389 \
   --server localhost \
   --domain '"$DC_DOMAIN"' \
   --password `cat /var/tmp/promote-pwd.txt`'

# 11  Add additional cifs entries to krb5.keytab
echo_status "Add additional cifs entries to krb5.keytab"
scp $TOOLS_DIR/add-keytab.sh $LIGHTWAVE_AD:/tmp
ssh root@$LIGHTWAVE_AD \
  /tmp/add-keytab.sh

# 12 Add gss-spnego plugin
echo_status "Installing CyrusSASL gssspnego plugin"
scp /home/abernstein/workspaces/wrk/cyrus-sasl-2.1.26/plugins/.libs/libgssspnego.so.3.0.0 abernstein@$LIGHTWAVE_AD:/var/tmp
ssh root@$LIGHTWAVE_AD \
  '( mv /var/tmp/libgssspnego.so.3.0.0 /usr/lib/sasl2 && ln -s /usr/lib/sasl2/libgssspnego.so.3.0.0 /usr/lib/sasl2/libgssspnego.so )'

# 13 Replace default GSSAPI plugin (built with GSS-SPNEGO disabled)
echo_status "Configuring patched libgssapiv2.so plugin that disables gss-spnego"
scp /home/abernstein/workspaces/wrk/cyrus-sasl-2.1.26/plugins/.libs/libgssapiv2.so.3.0.0 abernstein@$LIGHTWAVE_AD:/var/tmp
ssh root@$LIGHTWAVE_AD \
 '( mv -i /usr/lib/sasl2/libgssapiv2.so.3.0.0   /usr/lib/sasl2/libgssapiv2.so.3.0.0.rpmorig &&
    mv /var/tmp/libgssapiv2.so.3.0.0   /usr/lib/sasl2/libgssapiv2.so.3.0.0 )'

# 14 Replace the default CyrusSASL library
echo_status "Replace the default CyrusSASL library"
scp /home/abernstein/workspaces/wrk/cyrus-sasl-2.1.26/./lib/.libs/libsasl2.so.3.0.0 abernstein@$LIGHTWAVE_AD:/var/tmp
ssh root@$LIGHTWAVE_AD \
    '( mv /usr/lib/libsasl2.so.3.0.0  /usr/lib/libsasl2.so.3.0.0.rpmorig &&
       mv /var/tmp/libsasl2.so.3.0.0 /usr/lib/libsasl2.so.3.0.0 )'

# 15a Build correct name in partitions script
echo_status "Build partitions script"
cat  $TOOLS_DIR/partitions-vmdir.sh | \
  sed -e "s|DC_NAME|$DC_NAME|" -e "s|DC_DOMAIN|$DC_DOMAIN|" -e "s|DOMAIN_DN|$DOMAIN_DN|" > \
  /tmp/partitions-vmdir-edited.sh
chmod +x /tmp/partitions-vmdir-edited.sh

cat  $TOOLS_DIR/domain-attributes.sh | \
  sed -e "s|DC_NAME|$DC_NAME|" -e "s|DC_DOMAIN|$DC_DOMAIN|" -e "s|DOMAIN_DN|$DOMAIN_DN|" > \
  /tmp/domain-attributes-edited.sh 
chmod +x /tmp/domain-attributes-edited.sh 

# 15b copy and run partitions script to domain controller
echo_status "copy and run partitions script to domain controller"
scp /tmp/partitions-vmdir-edited.sh abernstein@$LIGHTWAVE_AD:/var/tmp/partitions-vmdir-edited.sh
ssh root@$LIGHTWAVE_AD /var/tmp/partitions-vmdir-edited.sh

echo_status "copy and run domain-attributes.sh to domain controller"
scp /tmp/domain-attributes-edited.sh abernstein@$LIGHTWAVE_AD:/var/tmp/domain-attributes-edited.sh
ssh root@$LIGHTWAVE_AD /var/tmp/domain-attributes-edited.sh


# 15a Get rid of the local provider; not relevant to a AD/DC
echo_status "Get rid of the local provider; not relevant to a AD/DC"
cat <<NNNN | ssh root@$LIGHTWAVE_AD cat > /tmp/regshell-loadorder.sh
/opt/likewise/bin/lwregshell set_value   '[HKEY_THIS_MACHINE\\Services\\lsass\Parameters\\Providers]' LoadOrder   ActiveDirectory VmDir 
NNNN
scp /tmp/regshell-loadorder.sh root@$LIGHTWAVE_AD:/tmp
ssh root@$LIGHTWAVE_AD sh /tmp/regshell-loadorder.sh

# 15b Configure the dsapi.conf file to use vmdirdb.so plugin
echo_status "Configure the dsapi.conf file to use vmdirdb.so plugin"
echo /opt/likewise/lib64/libvmdirdb.so | ssh root@$LIGHTWAVE_AD 'cat > /etc/likewise/dsapi.conf'

# 15c Add netlogin RPC server to lsassd
echo_status "Add netlogin RPC server to lsassd"
cat <<NNNN | ssh root@$LIGHTWAVE_AD cat > /tmp/regshell-rpcloadorder.sh
/opt/likewise/bin/lwregshell set_value   '[HKEY_THIS_MACHINE\\Services\\lsass\Parameters\\RPCServers]' LoadOrder   lsarpc samr dssetup wkssvc netlogon
/opt/likewise/bin/lwregshell add_key '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]'
/opt/likewise/bin/lwregshell add_value '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]' "HomeDirPrefix" REG_SZ "/home"
/opt/likewise/bin/lwregshell add_value '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]' "LoginShellTemplate" REG_SZ "/bin/sh"
/opt/likewise/bin/lwregshell add_value '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]' "LpcSocketPath" REG_SZ "/var/lib/likewise/rpc/lsass"
/opt/likewise/bin/lwregshell add_value '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]' "Path" REG_SZ "/opt/likewise/lib64/libnetlogon_srv.so"
/opt/likewise/bin/lwregshell add_value '[HKEY_THIS_MACHINE\\Services\\lsass\\Parameters\\RPCServers\\netlogon]' "RegisterTcpIp" REG_DWORD 0
NNNN
scp /tmp/regshell-rpcloadorder.sh root@$LIGHTWAVE_AD:/tmp
ssh root@$LIGHTWAVE_AD sh /tmp/regshell-rpcloadorder.sh


# 16 Restart all lightwave services
echo_status "Restart all lightwave services"
ssh root@$LIGHTWAVE_AD \
    /opt/likewise/bin/lwsm restart lwreg

# 17 get a copy of the krb5.keytab from DC
echo_status "get a copy of the krb5.keytab from DC"
scp root@$LIGHTWAVE_AD:/etc/krb5.keytab /tmp/krb5-`date +%s`.keytab

# 18 Ready for domainjoin-cli/Windows to join this system
echo_status "Ready for domainjoin-cli/Windows to join this system"
echo
echo "********************************************************"
echo "*   Lightwave DC is now configured: IP: $LIGHTWAVE_AD   "
echo "********************************************************"
