// FUNC_NAME: DynamicPointerArray::clearElementsAndDeallocate
void DynamicPointerArray::clearElementsAndDeallocate(void)
{
    int iIndex;
    int *pPointer; // Element pointer
    int iCount;    // Loop counter
    int *pAllocator; // Allocator structure
    int iElementIdx; // Index from allocation header

    // Iterate over elements from index 1 to m_count (inclusive)
    // Index 0 is reserved (sentinel or unused)
    for (iCount = 1; iCount <= this->m_count; iCount++)
    {
        pPointer = this->m_ppPointers[iCount];
        pAllocator = this->m_pAllocator;
        if (pPointer != (int *)0x0)
        {
            // Zero the allocator table entry for this allocation block
            // The allocation header at pPointer[-8] contains an index into the allocator's free list
            iElementIdx = *(int *)((int)pPointer + -8);
            *(int *)(*(int *)((int)pAllocator + 0xc) + iElementIdx * 4) = 0;
            // Decrement the allocator's allocation count
            *(int *)((int)pAllocator + 4) = *(int *)((int)pAllocator + 4) - 1;
            // Call the global deallocation function with the base of the allocated block
            (*(void (__cdecl *)(void *))DAT_01206694)((void *)((int)pPointer + -0x10));
        }
    }

    // Now free the array itself if it was dynamically allocated
    pPointer = this->m_ppPointers;
    // Check if the array pointer is not the embedded buffer and not null
    if ((pPointer != (int *)((int)this + 0x2174)) && (pPointer != (int *)0x0))
    {
        pAllocator = this->m_pAllocator;
        // Similar cleanup for the array allocation
        iElementIdx = *(int *)((int)pPointer + -8);
        *(int *)(*(int *)((int)pAllocator + 0xc) + iElementIdx * 4) = 0;
        *(int *)((int)pAllocator + 4) = *(int *)((int)pAllocator + 4) - 1;
        (*(void (__cdecl *)(void *))DAT_01206694)((void *)((int)pPointer + -0x10));
    }

    // Reset the capacity field (or some related tracking)
    this->m_capacity = 0;
}