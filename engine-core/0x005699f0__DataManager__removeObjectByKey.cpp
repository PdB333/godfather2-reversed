// FUNC_NAME: DataManager::removeObjectByKey
void DataManager::removeObjectByKey(void* param_1, undefined4 *param_2) // param_2: { const wchar_t* string; uint hash; }
{
    byte bChar1;
    int *pBucket;
    int iHashFromObject;
    int *pElement;
    undefined4 uVar5;
    byte *pObjectString;
    int *pObjectEntry;
    byte *pKeyString;
    bool bMatch;
    int *bucketArray;
    uint bucketIndex;
    uint bucketCount;
    byte *stringPtr;
    int hashResult;
    code *pDestructor;

    uVar5 = DAT_012233c0;  // global allocator
    enterCriticalSection(&DAT_00e2cbe8);  // lock
    bucketCount = 0;
    if (*(int *)(param_1 + 0x328) != 0) {  // number of buckets
        bucketArray = (int *)(param_1 + 0x228);  // pointer to bucket array
        do {
            pBucket = (int *)*bucketArray;  // get bucket pointer
            bucketIndex = 0;
            pElement = pBucket;  // start of elements in bucket
            if (pBucket[0x41] != 0) {  // number of objects in this bucket
                do {
                    iHashFromObject = pElement[1];  // hash from object
                    hashResult = getStringHashAndPointer(iHashFromObject + 8);  // returns hash and sets stringPtr
                    if (hashResult == param_2[1]) {  // compare hash
                        if (hashResult == 0) {
                            bMatch = true;
                        }
                        else {
                            pKeyString = (byte *)*param_2;  // key string pointer
                            pObjectString = stringPtr;
                            do {
                                bChar1 = *pObjectString;
                                bMatch = bChar1 < *pKeyString;
                                if (bChar1 != *pKeyString) {
                                    bMatch = (1 - bMatch) == (uint)(bMatch != 0);
                                    break;
                                }
                                if (bChar1 == 0) break;
                                bChar1 = pObjectString[1];  // wide char compare
                                bMatch = bChar1 < pKeyString[1];
                                if (bChar1 != pKeyString[1]) break;
                                pObjectString = pObjectString + 2;
                                pKeyString = pKeyString + 2;
                            } while (bChar1 != 0);
                            bMatch = true;
                        }
                    }
                    else {
                        bMatch = false;
                    }
                    if (stringPtr != (byte *)0x0) {
                        (*pDestructor)(stringPtr);  // free string? (unclear)
                    }
                    if (bMatch) {
                        pObjectEntry = (int *)getObjectFromPool(uVar5, iHashFromObject + 0x110);  // get object vtable
                        (**(code **)(*pObjectEntry + 0x18))(iHashFromObject);  // call destructor on object
                    }
                    bucketIndex = bucketIndex + 1;
                    pElement = pElement + 1;
                } while (bucketIndex < (uint)pBucket[0x41]);
            }
            bucketArray = bucketArray + 1;
            bucketCount = bucketCount + 1;
        } while (bucketCount < *(uint *)(param_1 + 0x328));
    }
    leaveCriticalSection();
    return;
}