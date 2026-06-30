// FUN_NAME: ReferenceManager::releaseResourceList (0x004f8530)

// Function at 0x004f8530: Releases a list of resource references by decrementing
// their reference counts. The list is embedded in the object structure.

// Structure layout (offsets in bytes):
// +0x00: unknown int (field_dword0)
// +0x04: unknown int (field_dword4)
// +0x08: array of pairs (IntPair) where each pair is { int resourceId; int userData; }
// +0x10: int count; // number of pairs (not separate – overlaps with first element of second pair)

// The function iterates over count pairs, decrements a global reference count array
// (indexed by resourceId), and frees the resource if the count reaches zero.

void ReferenceManager::releaseResourceList(IntPair* pairs, int count)
{
    if (count == 0) return;

    // Get the global reference count array pointer from thread-local storage
    // fs:0x2C -> pointer to TLS block -> deref -> pointer to global engine data
    // offset +8 from that gives base, then +0x30 is the reference count array.
    int** tlsPtr = (int**)__readfsdword(0x2C);
    int* globalBase = tlsPtr[0];
    int* refCountArray = (int*)(*(int*)((char*)globalBase + 8) + 0x30);

    for (int i = 0; i < count; i++)
    {
        int resourceId = pairs[i].first;  // piVar5[2] in first iteration, piVar5[2] in second is pairs[i+1].first? actually piVar5 advances by 2 ints each step
        if (resourceId != 0)
        {
            int userData = pairs[i].second; // piVar5[3]
            int* refCount = &refCountArray[resourceId];
            (*refCount)--;

            if (*refCount == 0)
            {
                // Resource reference count reached zero, free it
                FUN_00519340(resourceId, userData);
            }
        }
    }
}