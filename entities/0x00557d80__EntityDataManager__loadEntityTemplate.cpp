// FUNC_NAME: EntityDataManager::loadEntityTemplate
void __thiscall EntityDataManager::loadEntityTemplate(EntityDataManager *this, void *templateInfo, uint additionalParam1, uint additionalParam2)
{
    // +0x10 in templateInfo is likely a hash/key for the entity
    int newBlock;
    DataBlock *existingBlock;
    DataBlock *hashResult;

    // Lock or enter critical section for thread safety
    enterCriticalSection();
    TlsGetValue(s_threadLocalStorageIndex);

    // Allocate a new block of size 0x70 (112 bytes) with tag 0x27
    newBlock = operator_new(0x70, 0x27);
    *(ushort *)(newBlock + 4) = 0x70;  // store allocation size

    // Look up existing block from global hash table using key from templateInfo+0x10
    existingBlock = (DataBlock *)hashTableLookup(*(uint *)((int)templateInfo + 0x10), &s_dataBlockHashTable);
    initializeFromTemplate(templateInfo, additionalParam1, additionalParam2);

    // Decrement reference count on existing block and possibly delete if it reaches zero
    if (*(short *)((int)existingBlock + 4) != 0)
    {
        *(short *)((int)existingBlock + 6) = *(short *)((int)existingBlock + 6) - 1;
        if (*(short *)((int)existingBlock + 6) == 0)
        {
            // Call destructor via vtable (first function pointer)
            (*(void (**)(int))(*existingBlock))(1);
        }
    }

    // Look up a specific hash (0xab3e734) – likely a string constant like "instance"
    hashResult = (DataBlock *)lookupByCrc(localBuffer, 0xab3e734);
    existingBlock[2] = *hashResult;  // copy first word into offset 8

    // Mark this manager as initialized
    *(byte *)((int)this + 0x48) = 1;
}