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

#ifndef __MutentCADBAPI_H__
#define __MutentCADBAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

DWORD
LwCADbInitCtx(
    PLWCA_JSON_OBJECT pConfig
    );

DWORD
LwCADbAddCA(
    PCSTR                   pcszCAId,
    PLWCA_DB_CA_DATA        pCAData,
    PCSTR                   pcszParentCAId
    );

DWORD
LwCADbAddCertData(
    PCSTR                   pcszCAId,
    PLWCA_DB_CERT_DATA      pCertData
    );

DWORD
LwCADbCheckCA(
    PCSTR                   pcszCAId,
    PBOOLEAN                pbExists
    );

DWORD
LwCADbCheckCertData(
    PCSTR                   pcszCAId,
    PCSTR                   pcszSerialNumber,
    PBOOLEAN                pbExists
    );

DWORD
LwCADbGetCA(
    PCSTR                   pcszCAId,
    PLWCA_DB_CA_DATA        *ppCAData
    );

DWORD
LwCADbGetCAStatus(
    PCSTR                   pcszCAId,
    PLWCA_CA_STATUS         pStatus
    );

DWORD
LwCADbGetCAAuthBlob(
    PCSTR                   pcszCAId,
    PSTR                    *ppszAuthBlob
    );

DWORD
LwCADbGetCACertificates(
    PCSTR                      pcszCAId,
    PLWCA_CERTIFICATE_ARRAY    *ppCertArray
    );

DWORD
LwCADbLockCA(
    PCSTR   pcszCAId,
    PSTR    *ppszUuid
    );

DWORD
LwCADbUnlockCA(
    PCSTR   pcszCAId,
    PCSTR   pcszUuid
    );

DWORD
LwCADbLockCert(
    PCSTR   pcszCAId,
    PCSTR   pcszSerialNumber,
    PSTR    *ppszUuid
    );

DWORD
LwCADbUnlockCert(
    PCSTR   pcszCAId,
    PCSTR   pcszSerialNumber,
    PCSTR   pcszUuid
    );

DWORD
LwCADbGetCertData(
    PCSTR                       pcszCAId,
    PLWCA_DB_CERT_DATA_ARRAY    *ppCertDataArray
    );

DWORD
LwCADbGetCACRLNumber(
    PCSTR   pcszCAId,
    PSTR    *ppszCRLNumber
    );

DWORD
LwCADbGetParentCAId(
    PCSTR   pcszCAId,
    PSTR    *ppszParentCAId
    );

DWORD
LwCADbUpdateCA(
    PCSTR                   pcszCAId,
    PLWCA_DB_CA_DATA        pCAData
    );

DWORD
LwCADbUpdateCAStatus(
    PCSTR                pcszCAId,
    LWCA_CA_STATUS       status
    );

DWORD
LwCADbUpdateCertData(
    PCSTR                   pcszCAId,
    PLWCA_DB_CERT_DATA      pCertData
    );

DWORD
LwCADbUpdateCACRLNumber(
    PCSTR   pcszCAId,
    PCSTR   pcszCRLNumber
    );

VOID
LwCADbFreeCAData(
    PLWCA_DB_CA_DATA pCAData
    );

VOID
LwCADbFreeCertData(
    PLWCA_DB_CERT_DATA pCertData
    );

VOID
LwCADbFreeCertDataArray(
    PLWCA_DB_CERT_DATA_ARRAY pCertDataArray
    );

VOID
LwCADbFreeCtx(
   VOID
   );

#ifdef __cplusplus
}
#endif

#endif // __MutentCADBAPI_H__
