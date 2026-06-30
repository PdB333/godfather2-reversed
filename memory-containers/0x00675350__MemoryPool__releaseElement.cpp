// FUNC_NAME: MemoryPool::releaseElement
void __thiscall MemoryPool::releaseElement(void)
{
    if (this == nullptr) return;

    int* dataArray = this->mDataArray;          // offset 0x00
    int* sibling   = this->mSibling;            // offset 0x10

    if (sibling != nullptr) {
        // Clear the allocation table entry for the sibling
        // table is stored at dataArray + 0x0C (12 bytes)
        int* table = (int*)(dataArray + 3);      // offset 0x0C
        int index = sibling[-2];                  // offset -8 from sibling
        table[index] = 0;

        // Decrement reference count at dataArray + 0x04
        (*((int*)(dataArray + 1)))--;             // offset 0x04

        // Free the sibling's allocated block (header at sibling - 0x10)
        // Global deallocation function (DAT_01206694)
        (*((void (*)(void*))(DAT_01206694)))((void*)((int)sibling - 0x10));
    }

    // Now release the current element's own allocation
    dataArray = this->mDataArray;                // refresh
    int* table = (int*)(dataArray + 3);          // offset 0x0C
    int myIndex = this[-2];                       // offset -8 from this
    table[myIndex] = 0;

    (*((int*)(dataArray + 1)))--;                 // offset 0x04

    // Free this element's block (header at this - 4)
    (*((void (*)(void*))(DAT_01206694)))((void*)((int)this - 4));
}