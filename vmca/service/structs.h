/*
 * Copyright © 2012-2018 VMware, Inc.  All Rights Reserved.
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



/*
 * Module Name: VMCA
 *
 * Filename: structs.h
 *
 * Abstract:
 *
 * Structure definitions
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _VMCA_ENDPOINT
{
    PCSTR pszProtSeq;
    PCSTR pszEndpoint;
} VMCA_ENDPOINT, *PVMCA_ENDPOINT;

#ifdef REST_ENABLED

typedef enum
{
    VMCA_AUTHORIZATION_TYPE_UNDEFINED = 0,
    VMCA_AUTHORIZATION_TYPE_BEARER_TOKEN,
    VMCA_AUTHORIZATION_TOKEN_TYPE_KRB,
    VMCA_AUTHORIZATION_TYPE_HOTK_TOKEN,
    VMCA_AUTHORIZATION_TOKEN_TYPE_MAX
} VMCA_AUTHORIZATION_TYPE;

typedef struct _VMCA_ACCESS_TOKEN
{
    VMCA_AUTHORIZATION_TYPE  tokenType;
    PCSTR pszSubjectName;
    int* bKrbTicketValid;
    const PSTR* pszGroups;
    DWORD dwGroupSize;
//    union
//    {
        POIDC_ACCESS_TOKEN pOidcToken;
//    }
} VMCA_ACCESS_TOKEN, *PVMCA_ACCESS_TOKEN;

typedef struct _VMCA_HTTP_REQ_OBJ {
    PSTR                            pszMethod;
    PSTR                            pszUri;
    PSTR                            pszVer;
    PSTR                            pszConnection;
    PSTR                            pszTransferEncoding;
    PSTR                            pszContentLength;
    PSTR                            pszAuthorization;
    PSTR                            pszContentType;
    PSTR                            pszDate;
    PSTR                            pszPayload;
    FILE*                           debugFile;
    PVMCA_ACCESS_TOKEN              pAccessToken;
} VMCA_HTTP_REQ_OBJ, *PVMCA_HTTP_REQ_OBJ;

typedef struct _VMCA_AUTHORIZATION_PARAM
{
    PSTR pszAuthorizationToken;
    VMCA_AUTHORIZATION_TYPE tokenType;
} VMCA_AUTHORIZATION_PARAM, *PVMCA_AUTHORIZATION_PARAM;

typedef DWORD (*VMCA_ACCESS_TOKEN_VERIFY) (
    PVMCA_AUTHORIZATION_PARAM pAuthorization,
    VMCA_HTTP_REQ_OBJ*  pVMCARequest,
    PVMCA_ACCESS_TOKEN* ppAccessToken
    );

typedef VOID (*VMCA_ACCESS_TOKEN_FREE) (
    PVMCA_ACCESS_TOKEN pAccessToken
    );

typedef struct _VMCA_ACCESS_TOKEN_METHODS
{
    VMCA_AUTHORIZATION_TYPE       type;
    VMCA_ACCESS_TOKEN_VERIFY      pfnVerify;
    VMCA_ACCESS_TOKEN_FREE        pfnFree;
} VMCA_ACCESS_TOKEN_METHODS;

#endif

#ifdef _WIN32
typedef struct _VMCA_NTSERVICE_DATA
{
    SERVICE_STATUS_HANDLE hServiceStatus;
    HANDLE stopServiceEvent;
} VMCA_NTSERVICE_DATA, *PVMCA_NTSERVICE_DATA;

#endif // _WIN32


#ifdef __cplusplus
}
#endif
