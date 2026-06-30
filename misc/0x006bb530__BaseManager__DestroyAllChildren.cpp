// FUNC_NAME: BaseManager::DestroyAllChildren
void BaseManager::DestroyAllChildren(int* thisPtr)
{
    // Guard: null or already destroyed?
    if (thisPtr == nullptr || thisPtr[0x2e4] != 0)
        return;

    // Virtual call at vtable offset 0x1fc - get version or count
    uint currentVersion = GetCurrentVersion();
    uint itemCount = ((uint (*)(void*))(*(int**)(thisPtr))[0x1fc/4])(thisPtr);

    // Version mismatch? Bail.
    if (itemCount != currentVersion)
        return;

    IteratorState iterator;
    int* currentItem = thisPtr; // Will be overwritten by IterateBegin

    // Initialize iteration over items starting at thisPtr + 8
    if (!IterateBegin(thisPtr + 8, &currentItem, &iterator))
        return;

    // Loop through all items, releasing each one
    uint i = 0;
    while (i < itemCount)
    {
        void* item = GetCurrentItem(currentItem);
        ReleaseItem(item);

        // Advance to next item; break if none left
        if (!IterateNext(iterator, &currentItem))
            break;
        i++;
    }

    // Clean up iterator
    DestroyIterator(iterator);

    // Switch vtable to "destroyed" state (label 0x6bae20)
    thisPtr[0x56] = (int)&vtable_Destroyed;

    // Perform additional cleanup on sub‑objects (byte offsets from this)
    char* byteThis = (char*)thisPtr;
    if (*(int*)(byteThis + 0x1c) != 0)
    {
        // Offset 0x1c stored a pointer, we add another 0x1c to it
        ReleaseSubObject(*(int*)(byteThis + 0x1c) + 0x1c);
    }
    *(int*)(byteThis + 0xc) = 0;
}