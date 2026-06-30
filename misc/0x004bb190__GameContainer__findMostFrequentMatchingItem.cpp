// FUNC_NAME: GameContainer::findMostFrequentMatchingItem
int __thiscall GameContainer::findMostFrequentMatchingItem(GameContainer* this, int filterId, int context, short* outMaxCount, bool (*conditionCallback)(Item* item, int* extra, int context))
{
    // Function pointer table for iterating over all items in the container
    typedef int (*NextItemFunc)();
    typedef void (*AdvanceFunc)();
    struct AllItemIteratorVTable {
        NextItemFunc getNextItem;
        AdvanceFunc advance;
    };
    AllItemIteratorVTable** allIteratorVTable = &PTR_FUN_00e35c28;  // global vtable

    // Initialize global iterator state
    FUN_004bc930();

    void* containerData = nullptr;
    if (this != nullptr && *(int*)((char*)this + 8) != 0) {
        containerData = this;
    }

    // Iterator state for scanning all items
    bool allItemsRemaining = (containerData != nullptr);  // local_38
    void* allIterState = containerData;                    // local_34

    // Temporary buffer for creating hash table entries (counts)
    char countEntryBuf[8]; // +0: item ID, +4: short count, +8: next pointer (not in buf but allocated)
    int stackBuf; // local_44 used as key for hash table

    // Phase 1: initialize a hash table mapping each item's ID to a count of 0
    while (allItemsRemaining || allIterState != nullptr) {
        int itemPtr = (*allIteratorVTable[0]->getNextItem)(); // get next item pointer
        FUN_004bc820(&stackBuf, itemPtr + 8); // create or get hash entry for item->id (offset +8)
        *(short*)(stackBuf + 4) = 0;          // set count to 0
        (*allIteratorVTable[0]->advance)();    // move to next
    }

    // Filtered iterator from container with context
    struct FilteredIterator {
        int (*getCurrent)();
        int dummy2;
        int (*advance)();
    };
    FilteredIterator* filteredIter;
    FUN_004bab20(&filteredIter, this, context);

    // Iterator state for filtered scan
    bool filteredRemaining = (filteredIter->getCurrent() != 0); // iStack_2c
    bool filteredIterValid = (filteredIter->advance() != 0);    // iStack_28

    // Phase 2: for each item in filtered set, if id matches filterId and condition passes, increment its count
    while (filteredRemaining || filteredIterValid) {
        int currentItem = filteredIter->getCurrent(); // iVar3 = item pointer
        int entryKey = -1;  // local_44, reused as extra for callback
        if (*(int*)(currentItem + 8) == filterId) {
            int callbackResult = conditionCallback((Item*)currentItem, &entryKey, context);
            if (callbackResult != 0) {
                FUN_004bc820(&stackBuf, &entryKey); // get or create hash entry (key is entryKey)
                *(short*)(stackBuf + 4) += 1;        // increment count
            }
        }
        filteredIter->advance(); // move to next
    }

    // Phase 3: find the entry with maximum count
    void* hashTable = nullptr;
    if (/* local_20 */ this != nullptr) {
        // hashTable = **((int**)(local20+8));  // local_20 is a pointer to the hash table
        hashTable = *(void**)(*(int*)((char*)this + 8) + 0); // rough: dereference twice
    } else {
        hashTable = nullptr;
    }

    int bestId = -1;       // uVar5
    short maxCount = 0;     // sVar4

    // Iterate over linked list of hash entries (each entry: +0 = ID, +4 = short count, +8 = next)
    for (void* entry = hashTable; entry != nullptr; entry = *(void**)((char*)entry + 8)) {
        short currentCount = *(short*)((char*)entry + 4); // count at offset 4
        if (maxCount < currentCount) {
            bestId = *(int*)entry;  // ID at offset 0
            maxCount = currentCount;
        }
    }

    *outMaxCount = maxCount;

    // Cleanup
    FUN_004bc7d0(); // pop iterator state
    FUN_009c8f10(/* uStack_c */); // release some temporary
    if (this != nullptr) {
        FUN_009c8f10(*(void*)((char*)this + 8)); // release hash table?
        FUN_009c8eb0(this); // destroy container?
    }

    return bestId;
}