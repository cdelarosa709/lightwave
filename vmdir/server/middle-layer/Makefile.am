#
# Copyright (c) VMware Inc.  All rights Reserved.
# Module Name: middle-layer Makefile
# Abstract: VMware Cloud Directory Platform.
# Created on: Oct 4, 2011
# Author: Sanjay Jain (sanjain@vmware.com)
#         Sriram Nambakam (snambakam@vmware.com)
#

noinst_LTLIBRARIES = libmiddle-layer.la

libmiddle_layer_la_SOURCES = \
    add.c \
    bind.c \
    computedattribute.c \
    delete.c \
    dn.c \
    globals.c \
    groupplugin.c \
    indexplugin.c \
    krb.c \
    lockoutpolicy.c \
    modify.c \
    pagedsearch.c \
    password.c \
    plugin.c \
    pscache.c \
    replplugin.c \
    sasl.c \
    saslsockbuf.c \
    schema.c \
    search.c \
    specialsearch.c \
    srputil.c \
    util.c \
    usn.c \
    writequeue.c \
    libmain.c

libmiddle_layer_la_CPPFLAGS = \
    -I$(top_srcdir)/vmdir/include \
    -I$(top_srcdir)/vmdir/include/public \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/include \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/libraries/liblber \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/libraries/libldap \
    -I$(top_srcdir)/vmdir/server/include \
    -I$(top_srcdir)/vmcommon/include/public \
    @OPENSSL_INCLUDES@ \
    @LW_INCLUDES@

libmiddle_layer_la_LDFLAGS = \
    -static

