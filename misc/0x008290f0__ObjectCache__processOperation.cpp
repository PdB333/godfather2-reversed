// FUNC_NAME: ObjectCache::processOperation

int ObjectCache::processOperation(int* key, int param3, uint32_t flags, int operation)
{
    int* objectNode;
    int bucket[2];
    int local_10;
    int local_c;
    int savedOperation = operation;

    if (operation == 0 || operation == 3)
    {
        if (flags != 0)
        {
            int hash1 = FUN_00828280(); // thread-specific hash?
            FUN_00828b30(bucket, &hash1);
            int bucketEntry = bucket[0];

            // Check if bucket entry is end marker or empty
            if (bucketEntry == *(int*)(g_hashTablePointer + g_hashTableSize * 4) ||
                (objectNode = *(int**)(bucketEntry + 4), objectNode == nullptr))
            {
                FUN_0044e6d0(0x580e3e39, key, param3, flags, savedOperation);
                int classId = FUN_0044ede0(key);
                void* memory = FUN_009c8e50(0x40); // 64 bytes
                if (memory == nullptr)
                {
                    objectNode = nullptr;
                }
                else
                {
                    objectNode = (int*)FUN_00827fe0(classId);
                }

                // Fill object's fields with key data (offsets 0x04, 0x08, 0x0c, 0x10)
                objectNode[1] = key[0];  // +0x04
                objectNode[2] = key[1];  // +0x08
                objectNode[3] = key[2];  // +0x0c
                objectNode[4] = key[3];  // +0x10

                // Call virtual functions at vtable offsets 4 and 8
                (*(void(**)(uint32_t))(*objectNode + 4))(flags);
                (*(void(**)(void))(*objectNode + 8))();

                int** slot1 = (int**)FUN_00829070(&hash1);
                *slot1 = objectNode;
            }
            else
            {
                // Increment reference count at offset 0x38
                objectNode[0xe]++;  // +0x38
            }

            // Compute second hash from all key parts
            int hash2 = ((key[0] * 0x21 + key[1]) * 0x21 + key[2]) * 0x21 + key[3];
            int** slot2 = (int**)FUN_00829070(&hash2);
            *slot2 = (int)objectNode;
        }
    }
    else if (operation == 2 || operation == 4)
    {
        // Release object: decrement reference count
        int hash2 = ((key[0] * 0x21 + key[1]) * 0x21 + key[2]) * 0x21 + key[3];
        FUN_00828b30(&local_10, &hash2);
        int objectPtr = *(int*)(local_10 + 4);
        int* refCount = (int*)(objectPtr + 0x38);
        (*refCount)--;
        FUN_00828850(bucket, local_10, local_c);
        if (!g_cleanupFlag)
        {
            FUN_00828d00(&g_cleanupFlag);
        }
        return 1;
    }
    else if (operation == 5)
    {
        int* valPtr = (int*)FUN_00445210(&local_10);
        int hash = *valPtr;
        FUN_00828b30(bucket, &hash);
        int bucketEntry = bucket[0];
        if (bucketEntry != *(int*)(g_anotherPointer + g_anotherSize * 4))
        {
            int objectBase = *(int*)(bucketEntry + 4);
            if (*(int*)(objectBase + 0x1c) != 0)  // +0x1c
            {
                if ((flags & 0x200) == 0)
                {
                    uint32_t someFlags = FUN_0044d8e0();
                    if (((someFlags ^ flags) & 0x200) == 0)
                    {
                        *(uint8_t*)(objectBase + 0x3c) = ~(uint8_t)flags & 1;  // +0x3c
                        return 1;
                    }
                }
                FUN_004aa7b0(flags);
                return 1;
            }
        }
    }
    else
    {
        return FUN_0044e6d0(0x580e3e39, key, param3, flags, operation);
    }

    return 1;
}