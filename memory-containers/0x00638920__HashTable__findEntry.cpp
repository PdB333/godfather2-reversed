// FUNC_NAME: HashTable::findEntry
// 0x00638920 - Finds an entry in a hash table by key (byte array with length).
// param_1 (ecx): this pointer to the hash table
// param_2: pointer to key data
// param_3: length of key in bytes
// +0x10: pointer to hash table bucket array (array of bucket headers)
// The hash table uses a simple bucket-chained hash. The hash function is a rolling hash
// that combines the key bytes with a factor of 0x20 per byte and the previous hash shifted right by 2.
void HashTable::findEntry(int thisPtr, byte* key, uint keyLen) {
    undefined4* bucketPtr;
    uint hash;
    int compareResult;
    uint remaining;
    byte* keyPtrA;
    byte* keyPtrB;
    uint idx;
    int diff;

    // Compute hash: rolling hash with shift
    // hash = keyLen ^ (key[0] + hash * 0x20 + (hash >> 2)) for each byte, but loop uses subtraction
    hash = (keyLen >> 5) + 1;
    idx = keyLen;
    remaining = keyLen;
    if (hash <= keyLen) {
        do {
            int pos = idx - 1;
            idx = idx - hash;
            remaining = remaining ^ (uint)key[pos] + remaining * 0x20 + (remaining >> 2);
        } while (hash <= idx);
    }

    // Get bucket for this hash (mod bucket count). Bucket array at +0x10, count is the second int in that struct
    // *(int**)(thisPtr+0x10) gives pointer to bucket array header, [2] is count
    bucketPtr = *(undefined4**)(**(int**)(thisPtr + 0x10) + ((*(int**)(thisPtr + 0x10))[2] - 1U & remaining) * 4);

    do {
        if (bucketPtr == (undefined4*)0x0) {
            // Not found, insert via FUN_00638840 (likely hashTableInsert)
            FUN_00638840(thisPtr, key, keyLen);
            return;
        }
        // Check key length match (bucketPtr[3] stores key length)
        if (bucketPtr[3] == keyLen) {
            keyPtrA = (byte*)(bucketPtr + 4); // pointer to key data stored after header
            remaining = keyLen;
            keyPtrB = key;
            if (3 < keyLen) {
                do {
                    if (*(int*)keyPtrB != *(int*)keyPtrA) goto compareRemaining;
                    remaining = remaining - 4;
                    keyPtrA = keyPtrA + 4;
                    keyPtrB = keyPtrB + 4;
                } while (3 < remaining);
            }
            if (remaining == 0) {
                compareResult = 0;
            } else {
                // Compare remaining bytes
                diff = (uint)*keyPtrB - (uint)*keyPtrA;
                if (diff == 0) {
                    if (remaining == 1) goto equalFound;
                    diff = (uint)keyPtrB[1] - (uint)keyPtrA[1];
                    if (diff == 0) {
                        if (remaining == 2) goto equalFound;
                        diff = (uint)keyPtrB[2] - (uint)keyPtrA[2];
                        if (diff == 0) {
                            if (remaining == 3) goto equalFound;
                            diff = (uint)keyPtrB[3] - (uint)keyPtrA[3];
                            if (diff == 0) goto equalFound;
                        }
                    }
                }
                compareResult = 1;
                if (diff < 1) {
                    compareResult = -1;
                }
            }
            if (compareResult == 0) {
                return; // Found exact match
            }
        }
        bucketPtr = (undefined4*)*bucketPtr; // follow chain to next bucket
    } while (true);
}