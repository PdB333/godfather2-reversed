// FUNC_NAME: EARSFramework::Array::insertMultiple
// Address: 0x00651d30
// Reconstructed from Ghidra decompilation. Handles insertion of 4‑byte elements with reallocation support.
// Allocator structure at param_5 has a free‑list pointer at offset +0x14 (pointer to two sequential pointers).

void* __cdecl EARSFramework::Array::insertMultiple
(
    void* pDest,         // destination start (new buffer after reallocation)
    void* pInsertPos,    // insertion point in current buffer
    int   nInsertCount,  // number of elements to insert
    int   nCapacity,     // current capacity (in elements)
    void* pAllocator     // pointer to allocator structure
)
{
    int     nAllocCapacity;
    void*   pNewBuf;
    void**  ppFreeList;
    int     nElementCount;
    int     nMoveBytes;
    int     nUninitialized; // local_14 – likely a leftover register value

    // Case 1: insertion count fits into capacity and also into allocator's max capacity
    if (nInsertCount <= nCapacity)
    {
        nAllocCapacity = getGlobalCapacity(); // FUN_00651610 – maybe max allocatable?
        if (nInsertCount <= nAllocCapacity)
        {
            ppFreeList = *(void***)((char*)pAllocator + 0x14);
            ppFreeList[1] = (void*)(ppFreeList[0]); // reset free list tail → head (stack push?)

            pNewBuf = reallocateBuffer(pDest); // FUN_00651c20 – returns new buffer in EAX
            if (nUninitialized != 0)           // likely a hidden deallocation of old buffer
                deallocateBlock((void*)nUninitialized); // FUN_009c8eb0

            // Move elements before insertion point from old buffer to new buffer
            nElementCount = ((int)pInsertPos - (int)pNewBuf) >> 2;
            if (nElementCount > 0)
            {
                nMoveBytes = nElementCount * 4;
                memmove_s(pDest, nMoveBytes, pNewBuf, nMoveBytes);
            }

            // Move elements from free list to fill the gap after insertion point?
            void* pFreeHead = (void*)*ppFreeList;
            nElementCount = ((int)ppFreeList[1] - (int)pFreeHead) >> 2;
            pInsertPos = (void*)((int)pInsertPos - nElementCount * 4);
            if (nElementCount > 0)
            {
                nMoveBytes = nElementCount * 4;
                memmove_s(pInsertPos, nMoveBytes, pFreeHead, nMoveBytes);
            }
            return pInsertPos;
        }
    }

    // Case 2: insertion count doesn't fit into capacity but fits into allocator capacity (reverse direction)
    nAllocCapacity = getGlobalCapacity();
    if (nCapacity <= nAllocCapacity)
    {
        ppFreeList = *(void***)((char*)pAllocator + 0x14);
        ppFreeList[1] = (void*)(ppFreeList[0]);

        (void)reallocateBuffer(); // FUN_00651c20 – argument missing in decompiled? Assume no.

        if (nUninitialized != 0)
            deallocateBlock((void*)nUninitialized);

        // Move elements after insertion point from old buffer to new buffer
        nElementCount = ((int)pNewBuf - (int)pDest) >> 2; // pNewBuf is the return of reallocateBuffer (in EAX)
        if (nElementCount > 0)
        {
            nMoveBytes = nElementCount * 4;
            memmove_s((void*)((int)pInsertPos - nElementCount * 4), nMoveBytes, pDest, nMoveBytes);
        }

        // Move free list elements to the beginning of the new buffer
        void* pFreeHead = (void*)*ppFreeList;
        nElementCount = ((int)ppFreeList[1] - (int)pFreeHead) >> 2;
        nMoveBytes = nElementCount * 4;
        if (nElementCount > 0)
        {
            memmove_s(pDest, nMoveBytes, pFreeHead, nMoveBytes);
        }
        return (void*)(nMoveBytes + (int)pDest);
    }

    // Case 3: no reallocation, just shift elements in place
    if ((pDest != pNewBuf) && (pNewBuf != pInsertPos))
    {
        shiftElementsInPlace(pDest, pInsertPos); // FUN_00652420 – likely a memmove of remaining block
    }
    return (void*)((int)pDest + nCapacity * 4);
}