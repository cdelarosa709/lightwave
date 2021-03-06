/*
 * Copyright © 2012-2015 VMware, Inc.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the “License”); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, without
 * warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */





#ifndef _WIN32

#define VMDIR_OPTION_BOOTSTRAP_SCHEMA_FILE  'f'
#define VMDIR_OPTION_LOGGING_LEVEL          'l'
#define VMDIR_OPTION_LOG_FILE_NAME          'L'
#define VMDIR_OPTION_LDAP_PORT              'p'
#define VMDIR_OPTION_ENABLE_SYSLOG          's'
#define VMDIR_OPTION_CONSOLE_MODE           'c'
#define VMDIR_OPTION_RUN_MODE               'm' // Start server in restore or stand-alone mode
#define VMDIR_OPTIONS_VALID                 "f:l:L:p:scm:"

#define VMDIR_IF_HANDLE_T rpc_if_handle_t
#define VMDIR_RPC_BINDING_VECTOR_P_T rpc_binding_vector_p_t
#define VMDIR_RPC_AUTHZ_HANDLE rpc_authz_handle_t
#define VMDIR_RPC_BINDING_HANDLE rpc_binding_handle_t
#define VMDIR_RPC_C_AUTHN_LEVEL_PKT rpc_c_authn_level_pkt


#define VMDIR_MAX_CONFIG_VALUE_LENGTH   2048
#define VMDIR_CONFIG_PARAMETER_PARAMS_KEY_PATH "Services\\vmdir\\Parameters"
#define VMDIR_CONFIG_CREDS_KEY_PATH     "Services\\vmdir\\Parameters\\Credentials"

#define VMDIR_ADDR_INFO_NEXT( ifa ) ifa->ifa_next
#define VMDIR_ADDR_INFO_FLAGS( ifa ) ifa->ifa_flags
#define VMDIR_ADDR_INFO_ADDR( ifa ) ifa->ifa_addr

#else // #ifndef _WIN32

#define REG_DATA_TYPE DWORD
#define VMDIR_OPTION_BOOTSTRAP_SCHEMA_FILE  "-f"
#define VMDIR_OPTION_LOGGING_LEVEL          "-l"
#define VMDIR_OPTION_LOG_FILE_NAME          "-L"
#define VMDIR_OPTION_LDAP_PORT              "-p"
#define VMDIR_OPTION_ENABLE_SYSLOG          "-s"
#define VMDIR_OPTION_CONSOLE_MODE           "-c"
#define VMDIR_OPTION_RUN_MODE               "-m" // Start server in restore or stand-alone mode

#if defined(HAVE_DCERPC_WIN32)
#define VMDIR_IF_HANDLE_T rpc_if_handle_t
#define VMDIR_RPC_BINDING_VECTOR_P_T rpc_binding_vector_p_t
#define VMDIR_RPC_AUTHZ_HANDLE rpc_authz_handle_t
#define VMDIR_RPC_BINDING_HANDLE rpc_binding_handle_t
#define VMDIR_RPC_C_AUTHN_LEVEL_PKT rpc_c_authn_level_pkt

#else

/* MS-RPC case */
#define VMDIR_IF_HANDLE_T RPC_IF_HANDLE
#define VMDIR_RPC_BINDING_VECTOR_P_T RPC_BINDING_VECTOR*
#define VMDIR_RPC_AUTHZ_HANDLE RPC_AUTHZ_HANDLE
#define VMDIR_RPC_BINDING_HANDLE RPC_BINDING_HANDLE
#define VMDIR_RPC_C_AUTHN_LEVEL_PKT RPC_C_AUTHN_LEVEL_PKT
#endif

#define VMDIR_NT_SERVICE_NAME _T("VMWareDirectoryService")

#define VMDIR_CLOSE_HANDLE(handle) \
    {                              \
        if ((handle) != NULL)      \
        {                          \
            CloseHandle((handle)); \
            (handle) = NULL;       \
        }                          \
    }

#define VMDIR_CLOSE_SERVICE_HANDLE(hServiceHandle) \
    {                                              \
         if ( (hServiceHandle) != NULL )           \
         {                                         \
             CloseServiceHandle((hServiceHandle)); \
             (hServiceHandle) = NULL;              \
         }                                         \
    }

#define VMDIR_MAX_CONFIG_VALUE_LENGTH   2048
#define VMDIR_CONFIG_PARAMETER_PARAMS_KEY_PATH _T("SYSTEM\\CurrentControlSet\\services\\VMWareDirectoryService\\Parameters")
#define VMDIR_CONFIG_CREDS_KEY_PATH     _T("SYSTEM\\CurrentControlSet\\services\\VMWareDirectoryService\\Parameters\\Credentials")


#define VMDIR_ADDR_INFO_NEXT( ai ) ai->ai_next
#define VMDIR_ADDR_INFO_FLAGS( ai ) ai->ai_flags
#define VMDIR_ADDR_INFO_ADDR( ai ) ai->ai_addr

#endif

#define SUPPORTED_STATUS_COUNT    7

#define VMDIR_RPC_FLAG_ALLOW_NCALRPC         0x01
#define VMDIR_RPC_FLAG_ALLOW_TCPIP           0x02
#define VMDIR_RPC_FLAG_REQUIRE_AUTH_NCALRPC  0x04
#define VMDIR_RPC_FLAG_REQUIRE_AUTH_TCPIP    0x08
#define VMDIR_RPC_FLAG_REQUIRE_AUTHZ         0x10

//
// For every N tombstones that we reap we'll sleep X seconds to prevent us from
// taxing the server too much.
//
#define TOMBSTONE_REAPING_THROTTLE_COUNT 5

#define VDIR_INTEGRITY_CHECK_BATCH     1000

#ifdef LIGHTWAVE_BUILD
#define ACTIVE_LDAP_PORT_STR   DEFAULT_LDAP_PORT_STR "\000"
#define ACTIVE_LDAPS_PORT_STR  DEFAULT_LDAPS_PORT_STR "\000"
#else
#define ACTIVE_LDAP_PORT_STR   DEFAULT_LDAP_PORT_STR "\000" LEGACY_DEFAULT_LDAP_PORT_STR "\000"
#define ACTIVE_LDAPS_PORT_STR  DEFAULT_LDAPS_PORT_STR "\000" LEGACY_DEFAULT_LDAPS_PORT_STR "\000"
#endif

#define VMDIR_INTEG_CHK_REPORTS_DIR     VMDIR_LOG_DIR VMDIR_PATH_SEP "integrity" VMDIR_PATH_SEP "reports"
#define VMDIR_INTEG_CHK_ARCHIVE_DIR     VMDIR_LOG_DIR VMDIR_PATH_SEP "integrity" VMDIR_PATH_SEP "archive"

/*
 * Table to define and initialize VMDIR configuration data.
 *
 * To add a new configuration key,
 * 1. define its name in vmdircommon.h
 * 2. define its entry in the table below and init default/cfg Value
 *
 * VMDIR_CONFIG_VALUE_TYPE_STRING <-> REG_SZ
 * VMDIR_CONFIG_VALUE_TYPE_MULTISTRING <-> REG_MULI_SZ
 * VMDIR_CONFIG_VALUE_TYPE_DWORD  <-> REG_DWORD
 * VMDIR_CONFIG_VALUE_TYPE_BOOLEAN <-> REG_DWORD
 *
 */

#define VMDIR_CONFIG_INIT_TABLE_INITIALIZER                      \
{                                                                \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_ALLOW_INSECURE_AUTH,\
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_DISABLE_VECS,       \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAP_LISTEN_PORTS,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_MULTISTRING,  \
        /*.RegDataType    = */ REG_MULTI_SZ,                     \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ ACTIVE_LDAP_PORT_STR,             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAPS_LISTEN_PORTS, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_MULTISTRING,  \
        /*.RegDataType    = */ REG_MULTI_SZ,                     \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ ACTIVE_LDAPS_PORT_STR,            \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAP_CONNECT_PORTS, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_MULTISTRING,  \
        /*.RegDataType    = */ REG_MULTI_SZ,                     \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ ACTIVE_LDAP_PORT_STR,             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAPS_CONNECT_PORTS,\
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_MULTISTRING,  \
        /*.RegDataType    = */ REG_MULTI_SZ,                     \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ ACTIVE_LDAPS_PORT_STR,            \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_HTTP_LISTEN_PORT,   \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 65535,                            \
        /*.dwDefault      = */ DEFAULT_HTTP_PORT_NUM,            \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_HTTPS_LISTEN_PORT,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 65535,                            \
        /*.dwDefault      = */ DEFAULT_HTTPS_PORT_NUM,           \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_HTTPS_API_LISTEN_PORT,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 65535,                            \
        /*.dwDefault      = */ DEFAULT_HTTPS_API_PORT_NUM,       \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAP_RECV_TIMEOUT_SEC,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 65535,                            \
        /*.dwDefault      = */ 180,                              \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAP_CONNECT_TIMEOUT_SEC,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ -1,                               \
        /*.dwDefault      = */ 3,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_MAX_OP_THREADS,     \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 4096,                             \
        /*.dwDefault      = */ 1024,                             \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_MAX_INDEX_SCAN,     \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 32,                               \
        /*.dwMax          = */ 8192,                             \
        /*.dwDefault      = */ 512,                              \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {   /*.pszName        = */ VMDIR_REG_KEY_SMALL_CANDIDATE_SET, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 16,                               \
        /*.dwMax          = */ 8192,                             \
        /*.dwDefault      = */ 32,                              \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_ALLOW_ADMIN_LOCKOUT,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_MAX_SIZELIMIT_SCAN, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ UINT32_MAX,                       \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_ALLOW_IMPORT_OP_ATTR,\
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_LDAP_SEARCH_TIMEOUT_SEC,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 65535,                            \
        /*.dwDefault      = */ 60,                               \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_TRACK_LAST_LOGIN_TIME,\
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_PAGED_SEARCH_READ_AHEAD,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_BOOLEAN,  \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_TOMBSTONE_EXPIRATION_IN_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0xFFFFFFFF,                       \
        /*.dwDefault      = */ 45 * 24 * 60 * 60,                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_TOMBSTONE_REAPING_FREQ_IN_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0xFFFFFFFF,                       \
        /*.dwDefault      = */ 24 * 60 * 60,                     \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_MAX_INTERNAL_SEARCH, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 0xFFFFFFFF,                       \
        /*.dwDefault      = */ 1000000,                          \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_OPERATIONS_THREAD_TIMEOUT_IN_MILLI_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 5000,                             \
        /*.dwMax          = */ 60000,                            \
        /*.dwDefault      = */ 20000,                            \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_REPL_CONSUMER_THREAD_TIMEOUT_IN_MILLI_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 5000,                             \
        /*.dwMax          = */ 60000,                            \
        /*.dwDefault      = */ 10000,                            \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_EFFICIENT_READ_OP,  \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 5,                                \
        /*.dwMax          = */ 10000,                            \
        /*.dwDefault      = */ 50,                               \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_EMPTY_PAGE_COUNT,   \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 1,                                \
        /*.dwMax          = */ 10,                               \
        /*.dwDefault      = */ 1,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_SUPPLIER_THREAD_TIMEOUT_IN_MILLI_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 5000,                             \
        /*.dwMax          = */ 60000,                            \
        /*.dwDefault      = */ 10000,                            \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
    {                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_WRITE_TIMEOUT_IN_MILLI_SEC, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 1,                                \
        /*.dwMax          = */ 120000,                           \
        /*.dwDefault      = */ 60000,                            \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
	{                                                            \
        /*.pszName        = */ VMDIR_REG_KEY_ENABLE_REGIONAL_MASTER, \
        /*.Type           = */ VMDIR_CONFIG_VALUE_TYPE_DWORD,    \
        /*.RegDataType    = */ REG_DWORD,                        \
        /*.dwMin          = */ 0,                                \
        /*.dwMax          = */ 1,                                \
        /*.dwDefault      = */ 0,                                \
        /*.dwValue        = */ 0,                                \
        /*.pszDefault     = */ NULL,                             \
        /*.pszValue       = */ NULL                              \
    },                                                           \
}
