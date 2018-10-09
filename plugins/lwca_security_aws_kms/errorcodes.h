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

#ifndef _LWCA_SECURITY_AWS_KMS_ERROR_H_
#define _LWCA_SECURITY_AWS_KMS_ERROR_H_


typedef struct _LWCA_SECURITY_AWS_KMS_ERROR_MAP_
{
    int         code;
    const char* name;
    const char* desc;
} LWCA_SECURITY_AWS_KMS_ERROR_MAP, *PLWCA_SECURITY_AWS_KMS_ERROR_MAP;

#define LWCA_SECURITY_AWS_KMS_ERROR_START              0
#define LWCA_SECURITY_AWS_KMS_NOMEM                    (LWCA_SECURITY_AWS_KMS_ERROR_START + ENOMEM)
#define LWCA_SECURITY_AWS_KMS_INVALID_PARAM            (LWCA_SECURITY_AWS_KMS_ERROR_START + EINVAL)
/* specific errors */
#define LWCA_SECURITY_AWS_KMS_MISSING_CAPS             (LWCA_SECURITY_AWS_KMS_ERROR_START + 200)
#define LWCA_SECURITY_AWS_KMS_NOT_IMPLEMENTED          (LWCA_SECURITY_AWS_KMS_ERROR_START + 201)
#define LWCA_SECURITY_AWS_KMS_ZERO_ENCRYPT_DATA        (LWCA_SECURITY_AWS_KMS_ERROR_START + 202)
#define LWCA_SECURITY_AWS_KMS_ENCRYPTION_ERROR         (LWCA_SECURITY_AWS_KMS_ERROR_START + 203)
#define LWCA_SECURITY_AWS_KMS_DECRYPTION_ERROR         (LWCA_SECURITY_AWS_KMS_ERROR_START + 204)
#define LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_DATA        (LWCA_SECURITY_AWS_KMS_ERROR_START + 205)
#define LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_KEY         (LWCA_SECURITY_AWS_KMS_ERROR_START + 206)
#define LWCA_SECURITY_AWS_KMS_GEN_DATA_KEY_ERROR       (LWCA_SECURITY_AWS_KMS_ERROR_START + 207)
#define LWCA_SECURITY_AWS_KMS_ENCRYPT_ERROR            (LWCA_SECURITY_AWS_KMS_ERROR_START + 208)
#define LWCA_SECURITY_AWS_KMS_DECRYPT_ERROR            (LWCA_SECURITY_AWS_KMS_ERROR_START + 209)
#define LWCA_SECURITY_AWS_KMS_INVALID_ENCRYPTED_DATA   (LWCA_SECURITY_AWS_KMS_ERROR_START + 210)
#define LWCA_SECURITY_AWS_KMS_ENCRYPTED_DATA_TOO_BIG   (LWCA_SECURITY_AWS_KMS_ERROR_START + 211)
#define LWCA_SECURITY_AWS_KMS_KEY_CREATION_ERROR       (LWCA_SECURITY_AWS_KMS_ERROR_START + 212)
#define LWCA_SECURITY_AWS_KMS_KEY_INVALID_LENGTH       (LWCA_SECURITY_AWS_KMS_ERROR_START + 213)
#define LWCA_SECURITY_AWS_KMS_KEY_CONVERSION_ERROR     (LWCA_SECURITY_AWS_KMS_ERROR_START + 214)
#define LWCA_SECURITY_AWS_KMS_SIGN_FAILED              (LWCA_SECURITY_AWS_KMS_ERROR_START + 215)
#define LWCA_SECURITY_AWS_KMS_VERIFY_FAILED            (LWCA_SECURITY_AWS_KMS_ERROR_START + 216)
#define LWCA_SECURITY_AWS_KMS_READ_PEM_ERROR           (LWCA_SECURITY_AWS_KMS_ERROR_START + 217)
#define LWCA_SECURITY_AWS_KMS_INVALID_MESSAGE_DIGEST   (LWCA_SECURITY_AWS_KMS_ERROR_START + 218)
#define LWCA_SECURITY_AWS_KMS_ENCRYPTED_MATERIAL_ERROR (LWCA_SECURITY_AWS_KMS_ERROR_START + 219)
/* last */
#define LWCA_SECURITY_AWS_KMS_UNKNOWN_ERROR            (LWCA_SECURITY_AWS_KMS_ERROR_START + 254)

#define LWCA_SECURITY_AWS_KMS_ERROR_INITIALIZER \
{ \
    { LWCA_SECURITY_AWS_KMS_UNKNOWN_ERROR,           "LWCA_SECURITY_AWS_KMS_UNKNOWN_ERROR", "Unknown error" }, \
    { LWCA_SECURITY_AWS_KMS_MISSING_CAPS,            "LWCA_SECURITY_AWS_KMS_MISSING_CAPS", "aws kms security implementation requires storage get and storage put capability overrides." }, \
    { LWCA_SECURITY_AWS_KMS_NOT_IMPLEMENTED,         "LWCA_SECURITY_AWS_KMS_NOT_IMPLEMENTED", "this functionality is not implemented." }, \
    { LWCA_SECURITY_AWS_KMS_ZERO_ENCRYPT_DATA,       "LWCA_SECURITY_AWS_KMS_ZERO_ENCRYPT_DATA", "encryption request has zero length data" }, \
    { LWCA_SECURITY_AWS_KMS_ENCRYPTION_ERROR,        "LWCA_SECURITY_AWS_KMS_ENCRYPTION_ERROR", "kms encryption error" }, \
    { LWCA_SECURITY_AWS_KMS_DECRYPTION_ERROR,        "LWCA_SECURITY_AWS_KMS_DECRYPTION_ERROR", "kms decryption error" }, \
    { LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_DATA,       "LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_DATA", "error decrypting data" }, \
    { LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_KEY,        "LWCA_SECURITY_AWS_KMS_ZERO_DECRYPT_KEY", "error decrypting data key" }, \
    { LWCA_SECURITY_AWS_KMS_ENCRYPT_ERROR,           "LWCA_SECURITY_AWS_KMS_ENCRYPT_ERROR", "error in local encrypt operation. check data." }, \
    { LWCA_SECURITY_AWS_KMS_DECRYPT_ERROR,           "LWCA_SECURITY_AWS_KMS_DECRYPT_ERROR", "error in local decrypt operation. check data." }, \
    { LWCA_SECURITY_AWS_KMS_INVALID_ENCRYPTED_DATA,  "LWCA_SECURITY_AWS_KMS_INVALID_ENCRYPTED_DATA", "encrypted data is invalid." }, \
    { LWCA_SECURITY_AWS_KMS_ENCRYPTED_DATA_TOO_BIG,  "LWCA_SECURITY_AWS_KMS_ENCRYPTED_DATA_TOO_BIG", "encrypted data is too large. check data." }, \
    { LWCA_SECURITY_AWS_KMS_KEY_CREATION_ERROR,      "LWCA_SECURITY_AWS_KMS_KEY_CREATION_ERROR", "error creating key pair." }, \
    { LWCA_SECURITY_AWS_KMS_KEY_INVALID_LENGTH,      "LWCA_SECURITY_AWS_KMS_KEY_INVALID_LENGTH", "invalid length specified for key. valid range is between 1024 and 16384." }, \
    { LWCA_SECURITY_AWS_KMS_KEY_CONVERSION_ERROR,    "LWCA_SECURITY_AWS_KMS_KEY_CONVERSION_ERROR", "error converting key to pem format." }, \
    { LWCA_SECURITY_AWS_KMS_SIGN_FAILED,             "LWCA_SECURITY_AWS_KMS_SIGN_FAILED", "error during x509 sign." }, \
    { LWCA_SECURITY_AWS_KMS_VERIFY_FAILED,           "LWCA_SECURITY_AWS_KMS_VERIFY_FAILED", "error during x509 verify." }, \
    { LWCA_SECURITY_AWS_KMS_READ_PEM_ERROR,          "LWCA_SECURITY_AWS_KMS_READ_PEM_ERROR", "error reading pem data." }, \
    { LWCA_SECURITY_AWS_KMS_INVALID_MESSAGE_DIGEST,  "LWCA_SECURITY_AWS_KMS_INVALID_MESSAGE_DIGEST", "invalid message digest specified." }, \
    { LWCA_SECURITY_AWS_KMS_ENCRYPTED_MATERIAL_ERROR,"LWCA_SECURITY_AWS_KMS_ENCRYPTED_MATERIAL_ERROR", "error validating or operating on encrypted key material. check data." }, \
};

#endif /*  _LWCA_SECURITY_AWS_KMS_ERROR_H_ */
