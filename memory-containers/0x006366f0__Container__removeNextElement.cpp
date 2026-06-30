// FUNC_NAME: Container::removeNextElement
int __thiscall Container::removeNextElement(void *thisPtr) {
    // local_18: 4-byte buffer used by getNextElement to output data (possibly pointer to element)
    char buffer[4]; // might be a void*
    int nextItem = 0;   // local_14 – pointer to the next item to be removed
    int itemSize = 0;    // local_10 – size/count associated with the item

    // getNextElement is likely a member function that retrieves the next element
    // Second argument is a callback function (address 0x00636660) that determines which element to remove.
    // Third argument 'buffer' receives output data (e.g., pointer to element)
    int result = getNextElement(thisPtr, (void*)0x00636660, buffer);

    int tmpSize = itemSize; // local_10 -> iVar2

    if (nextItem != 0) {
        // Call global destructor/deallocator for the item
        ((void (*)(int))DAT_012059e0)(nextItem);
        // Decrement the count stored at offset 0x24 from pointer at this+0x10
        int *countPtr = *(int**)((char*)thisPtr + 0x10) + 0x24 / sizeof(int);
        *countPtr -= tmpSize;
    }

    // Reset local variables (unnecessary but present)
    nextItem = 0;
    itemSize = 0;

    if (result != 0) {
        // Post-removal cleanup (e.g., reallocate or update internal state)
        postRemoveCleanup();
    }

    return result; // 0 if no element was removed, non-zero on success
}