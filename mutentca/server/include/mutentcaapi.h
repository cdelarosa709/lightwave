/*
 * Copyright © 2018 VMware, Inc.  All Rights Reserved.
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

#ifndef __MUTENT_CA_API_H__
#define __MUTENT_CA_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LWCA_INTERMEDIATE_CA_REQ_DATA
{
    PLWCA_STRING_ARRAY     pCountryList;
    PLWCA_STRING_ARRAY     pLocalityList;
    PLWCA_STRING_ARRAY     pStateList;
    PLWCA_STRING_ARRAY     pOUList;
    PSTR                   pszPolicy;
} LWCA_INTERMEDIATE_CA_REQ_DATA, *PLWCA_INTERMEDIATE_CA_REQ_DATA;

typedef PSTR PLWCA_CERTIFICATE;

typedef struct _LWCA_CERTIFICATE_ARRAY
{
    PLWCA_CERTIFICATE *ppCertificates;
    DWORD             dwCount;
} LWCA_CERTIFICATE_ARRAY, *PLWCA_CERTIFICATE_ARRAY;

typedef PSTR PLWCA_CRL;

typedef struct _LWCA_CERT_VALIDITY
{
    time_t tmNotBefore;
    time_t tmNotAfter;
} LWCA_CERT_VALIDITY, *PLWCA_CERT_VALIDITY;

typedef PSTR PLWCA_CERT_REQUEST;

typedef enum _LWCA_SIGNING_ALGORITHM
{
    LWCA_SHA_256 = 0
} LWCA_SIGNING_ALGORITHM, *PLWCA_SIGNING_ALGORITHM;

DWORD
LwCACreateCARequest(
    PLWCA_STRING_ARRAY              pCountryList,
    PLWCA_STRING_ARRAY              pLocalityList,
    PLWCA_STRING_ARRAY              pStateList,
    PLWCA_STRING_ARRAY              pOUList,
    PCSTR                           pcszPolicy,
    PLWCA_INTERMEDIATE_CA_REQ_DATA  *ppCARequest
    );

DWORD
LwCACreateCertValidity(
    time_t              tmNotBefore,
    time_t              tmNotAfter,
    PLWCA_CERT_VALIDITY *ppCertValidity
    );

DWORD
LwCACreateRootCA(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszRootCAId,
    PLWCA_CERTIFICATE       pCertificate,
    PCSTR                   pcszPrivateKey,
    PCSTR                   pcszPassPhrase
    );

DWORD
LwCACreateIntermediateCA(
    PLWCA_REQ_CONTEXT               pReqCtx,
    PCSTR                           pcszCAId,
    PCSTR                           pcszParentCAId,
    PLWCA_INTERMEDIATE_CA_REQ_DATA  pCARequest,
    PLWCA_CERT_VALIDITY             pValidity
    );

DWORD
LwCAGetSignedCertificate(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszCAId,
    PLWCA_CERT_REQUEST      pCertRequest,
    PLWCA_CERT_VALIDITY     pValidity,
    LWCA_SIGNING_ALGORITHM  signAlgorithm,
    PLWCA_CERTIFICATE       *ppCertifcate
    );

DWORD
LwCAGetCACertificates(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszCAId,
    PLWCA_CERTIFICATE_ARRAY *ppCertificates
    );

DWORD
LwCAGetCACrl(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszCAId,
    PLWCA_CRL               *ppCrl
    );

DWORD
LwCARevokeIntermediateCA(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszCAId
    );

DWORD
LwCARevokeCertificate(
    PLWCA_REQ_CONTEXT       pReqCtx,
    PCSTR                   pcszCAId,
    PLWCA_CERTIFICATE       pCertificate
    );

VOID
LwCAFreeCARequest(
    PLWCA_INTERMEDIATE_CA_REQ_DATA   pCAReqData
    );

VOID
LwCAFreeCertValidity(
    PLWCA_CERT_VALIDITY pCertValidity
    );

VOID
LwCAFreeCertRequest(
    PLWCA_CERT_REQUEST pCertRequest
    );

VOID
LwCAFreeCrl(
    PLWCA_CRL pCrl
    );

VOID
LwCAFreeCertificate(
    PLWCA_CERTIFICATE pCertificate
    );

VOID
LwCAFreeCertificates(
    PLWCA_CERTIFICATE_ARRAY ppCertificates
    );

#ifdef __cplusplus
}
#endif

#endif // __MUTENT_CA_API_H__