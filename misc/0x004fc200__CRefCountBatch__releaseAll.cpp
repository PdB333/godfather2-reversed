// FUNC_NAME: CRefCountBatch::releaseAll

void __thiscall CRefCountBatch::releaseAll(int* thisPtr)
{
    int* currentEntry; // piVar5
    unsigned int index; // uVar6
    int resourceId;    // iVar2
    int resourceSubId; // iVar4

    index = 0;
    currentEntry = thisPtr;
    if (thisPtr[0x16] != 0) { // +0x58: count of entries
        do {
            resourceId = currentEntry[2];    // current entry +0x08: resource ID
            if (resourceId != 0) {
                // Get global ref count pointer via thread-local storage
                int* globalBase = *(int**)(__readgsdword(0x2c)); // unaff_FS_OFFSET + 0x2c
                int* refCountTable = *(int**)(globalBase + 2);   // globalBase + 8 (offset 0x8)
                int* refCount = refCountTable + 0x30 / 4 + resourceId; // offset 0x30 + id*4
                resourceSubId = currentEntry[3]; // +0x0C: sub resource ID
                *refCount = *refCount - 1;
                if (*refCount == 0) {
                    // Resource reference count reached zero; release it
                    FUN_00519340(resourceId, resourceSubId);
                }
            }
            ++index;
            currentEntry += 2; // move to next pair (8 bytes stride)
        } while (index < (unsigned int)thisPtr[0x16]);
    }
}