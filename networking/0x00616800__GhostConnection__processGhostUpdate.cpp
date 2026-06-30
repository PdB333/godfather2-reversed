// FUNC_NAME: GhostConnection::processGhostUpdate
// Address: 0x00616800
// Role: Processes a stream of 5-byte ghost update records (type byte + 4 bytes data) to update object reference arrays, int32 property arrays, and perform ref counting.

void __thiscall GhostConnection::processGhostUpdate(
    void* thisPtr,
    GhostObject* ghostObj,
    int objectId,
    const char* streamData,
    int streamLen,
    char resetFlag
) {
    int countType0 = 0;
    int countType1 = 0;
    int countType2 = 0;

    char* dataPtr = streamData;
    int remaining = streamLen;

    // First pass: count occurrences of each record type
    if (streamLen > 0) {
        do {
            char recordType = *dataPtr;
            if (recordType == '\0') {
                countType0++;
            } else if (recordType == '\x01') {
                countType1++;
            } else if (recordType == '\x02') {
                countType2++;
            }
            remaining--;
            dataPtr += 5; // Each record is 5 bytes: 1 byte type + 4 bytes data
        } while (remaining != 0);

        // Allocate dynamic arrays for each type if needed and not already present
        if (countType0 != 0 && ghostObj->type0Array == nullptr) {
            uint8_t* alloc = (uint8_t*)FUN_009c8e50(0xc); // malloc(12)
            if (alloc != nullptr) {
                uint32_t* arrayBase = (uint32_t*)FUN_009c8e80(countType0 * 8); // malloc(count * 8)
                *(uint32_t*)alloc = (uint32_t)arrayBase;
                *(uint32_t*)(alloc + 4) = 0;                // used count
                *(uint32_t*)(alloc + 8) = countType0;       // capacity
                ghostObj->type0Array = (Type0Array*)alloc;
            }
        }
        if (countType1 != 0 && ghostObj->type1Array == nullptr) {
            uint8_t* alloc = (uint8_t*)FUN_009c8e50(0xc);
            if (alloc != nullptr) {
                uint32_t* arrayBase = (uint32_t*)FUN_009c8e80(countType1 * 8);
                *(uint32_t*)alloc = (uint32_t)arrayBase;
                *(uint32_t*)(alloc + 4) = 0;
                *(uint32_t*)(alloc + 8) = countType1;
                ghostObj->type1Array = (Type1Array*)alloc;
            }
        }
        if (countType2 != 0 && ghostObj->type2Array == nullptr) {
            uint8_t* alloc = (uint8_t*)FUN_009c8e50(0xc);
            if (alloc != nullptr) {
                uint32_t* arrayBase = (uint32_t*)FUN_009c8e80(countType2 * 8);
                *(uint32_t*)alloc = (uint32_t)arrayBase;
                *(uint32_t*)(alloc + 4) = 0;
                *(uint32_t*)(alloc + 8) = countType2;
                ghostObj->type2Array = (Type2Array*)alloc;
            }
        }
    }

    // If reset flag is set, clear existing arrays
    if (resetFlag != '\0') {
        if (ghostObj->type0Array != nullptr) {
            FUN_00617740(ghostObj->type0Array); // clear type0 array
        }
        if (ghostObj->type1Array != nullptr && ghostObj->type1Array->usedCount != 0) {
            ghostObj->type1Array->usedCount = 0;
        }
        if (ghostObj->type2Array != nullptr && ghostObj->type2Array->usedCount != 0) {
            ghostObj->type2Array->usedCount = 0;
        }
    }

    // Second pass: process each record
    if (streamLen > 0) {
        const char* curPtr = streamData;
        int key = objectId;
        do {
            char recordType = *curPtr;
            const char* valuePtr = curPtr + 1; // 4 bytes data follow

            if (recordType == '\0') {
                // Type 0: object reference update (hash map lookup/insert with ref count)
                int index = FUN_00617920(key); // find existing entry index for this key
                int* entryPtr;
                if (index < 0) {
                    entryPtr = (int*)FUN_00617440(ghostObj->type0Array, key); // insert new
                } else {
                    // Offset: array header[4 bytes] + index * 8
                    // The array pointer points to a header with 4-byte count, then 8-byte entries
                    entryPtr = (int*)(*(uint32_t*)(ghostObj->type0Array) + 4 + index * 8);
                }
                int newHandle = FUN_006163d0(); // get or create a ref-counted handle for key
                int oldHandle = *entryPtr;
                if (oldHandle != newHandle) {
                    if (oldHandle != 0) {
                        // Decrement ref count
                        short* refCount = (short*)(oldHandle + 8);
                        (*refCount)--;
                        if (*refCount == 0) {
                            FUN_00616dc0(oldHandle); // release
                            (**(code**)(*DAT_01205964 + 4))(oldHandle, 0); // destructor?
                        }
                        *entryPtr = 0;
                    }
                    if (newHandle != 0) {
                        short* refCount = (short*)(newHandle + 8);
                        (*refCount)++;
                        *entryPtr = newHandle;
                    }
                }
            } else if (recordType == '\x01') {
                // Type 1: int32 property set (via array getter)
                int* outPtr = nullptr;
                int* targetSlot = (int*)FUN_00617520(key, &outPtr);
                *targetSlot = *(int*)valuePtr;
            } else if (recordType == '\x02') {
                // Type 2: int32 property set (alternate array)
                int outValue = 0;
                int* targetSlot = (int*)FUN_006175e0(key, &outValue);
                *targetSlot = *(int*)valuePtr;
            }

            curPtr += 5;
            key += 4; // advance key by size of one 32-bit value? (each record modifies consecutive keys)
            streamLen--;
        } while (streamLen != 0);
    }
}