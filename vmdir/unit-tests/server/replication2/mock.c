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

#include "includes.h"

DWORD
__wrap_VmDirEntryGetAllMustAttrs(
    PVDIR_ENTRY     pEntry,
    PLW_HASHMAP*    ppAllMustAttrMap
    )
{
    DWORD          dwError = 0;
    PLW_HASHMAP    pAllMustAttrMap = NULL;

    dwError = LwRtlCreateHashMap(
            &pAllMustAttrMap,
            LwRtlHashDigestPstrCaseless,
            LwRtlHashEqualPstrCaseless,
            NULL);
    assert_int_equal(dwError, 0);

    dwError = LwRtlHashMapInsert(pAllMustAttrMap, ATTR_CN, NULL, NULL);
    assert_int_equal(dwError, 0);

    *ppAllMustAttrMap = pAllMustAttrMap;

    return 0;
}
