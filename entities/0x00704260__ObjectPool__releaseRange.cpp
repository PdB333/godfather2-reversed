// FUNC_NAME: ObjectPool::releaseRange
// Function at 0x00704260 releases a range of indices in an object pool,
// moving each object to an internal free list and decrementing the active count.
// param_1 (this): pointer to pool structure
//   +0x00: pArray - pointer to array of object handles (8 bytes each? actually larger)
//   +0x04: m_count - number of active objects
// Each handle (8 bytes at pArray + index*8) appears to contain:
//   offset 0: pObject (pointer to object or null)
//   offset 4: pNextFree (pointer to next free node)
//   offset 8: pFreeListHead (head of free list for this type?) – accessed via piVar1[2] but only when stepping by 8? Possibly a decompiler miscalculation.
// The function iterates indices from startIndex to m_count-2, re-linking each handle into the free list,
// then decrements m_count and performs a final cleanup if the last element exists.

void __thiscall ObjectPool::releaseRange(uint startIndex)
{
    PoolStruct* thisPool = reinterpret_cast<PoolStruct*>(this);
    int* pArray = thisPool->pArray;
    int count = thisPool->m_count;

    if (startIndex < count - 1U) {
        do {
            // piVar1 points to handle at index startIndex
            int* pHandle = &pArray[startIndex * 2]; // each handle is 8 bytes (2 ints)
            // pHandle+2? Actually the decompiler accesses piVar1[2], which would be 12 bytes from pHandle.
            // This suggests the handle struct is at least 12 bytes. Possibly the array element is larger (e.g., 12 bytes).
            // We'll treat the handle as having three fields: pObject, pNextFree, pFreeListHead.
            int* pNextFree = &pHandle[2]; // third int

            // If the handle is not the same as the next free node? (always true due to difference in address)
            if (pHandle != pNextFree) {
                int freeListHead = pHandle[2]; // third int holds address of free list head
                // If the current object pointer is different from freeListHead
                if (pHandle[0] != freeListHead) {
                    if (pHandle[0] != 0) {
                        // Destroy/cleanup the old object (FUN_004daf90 likely releases the object's memory)
                        ObjectDestructor(reinterpret_cast<void*>(pHandle));
                    }
                    // Set the object pointer to the free list head
                    pHandle[0] = freeListHead;
                    if (freeListHead != 0) {
                        // Insert this handle into the free list (singly linked list via pNextFree)
                        pHandle[1] = *(int*)(freeListHead + 4); // previous head's next
                        *(int**)(freeListHead + 4) = pHandle;   // head now points to this handle
                    }
                }
            }
            startIndex++;
        } while (startIndex < count - 1U);
    }
    // Decrement the active count
    thisPool->m_count--;

    // If the object at the new last slot exists, clean it up as well
    int* pLastHandle = &pArray[thisPool->m_count * 2];
    if (pLastHandle[0] != 0) {
        ObjectDestructor(reinterpret_cast<void*>(pLastHandle)); // no arguments in original? may need to pass pointer
    }
}