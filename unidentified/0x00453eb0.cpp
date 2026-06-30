// FUN_00453eb0: SomeClass::flushPendingList
void SomeClass::flushPendingList(void)
{
    // +0x14: pointer to list data (e.g., contains count and list pointer)
    int listPtr;     // local_c
    uint count;      // local_8 – initialized by getListData
    // Retrieve both count and pointer from the list data structure.
    // The call writes to count and listPtr (second output not shown in decompiler).
    getListData(*(int*)(this + 0x14), &count, &listPtr);

    uint i = 0;
    if (count != 0) {
        do {
            processPendingItem(this);   // FUN_00453d40
            i = i + 1;
        } while (i < count);
    }

    if (listPtr != 0) {
        freeMemory(listPtr);            // FUN_009c8f10 – likely operator delete
    }
    return;
}