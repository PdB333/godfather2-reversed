// FUNC_NAME: PoolManager::returnElementsByID
// Function address: 0x0066df80
// Purpose: Removes all elements with a given ID from the active list (param_1+0x14)
// and moves them to the free list (param_2+0x14). Updates size/count fields accordingly.

void __fastcall PoolManager::returnElementsByID(PoolManager* this, PoolFreeList* freeList, uint32_t id)
{
    PoolNode** ppActiveHead = reinterpret_cast<PoolNode**>(this + 0x14); // +0x14: active list head pointer
    PoolNode* pCurrent = *ppActiveHead;
    PoolNode* pPrev = nullptr;

    while (pCurrent != nullptr) {
        PoolNode* pNext = pCurrent->next; // pCurrent[0]
        if (pCurrent->id == id) { // pCurrent[1]
            // Update totals: subtract element's size from freeList accumulator
            *reinterpret_cast<int*>(reinterpret_cast<char*>(freeList) + 0x4) -= pCurrent->size; // +0x4: accumulator of total size freed
            // Subtract size from this->activeTotalSize (at +0xC)
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC) -= pCurrent->size;
            // Decrement active element count (at +0x10)
            --(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10));
            // Move node to free list
            pCurrent->next = freeList->freeHead; // freeList+0x14
            pCurrent->id = 0;
            pCurrent->size = 0;
            // Decrement freeList element count (short at +0x8)
            *reinterpret_cast<short*>(reinterpret_cast<char*>(freeList) + 0x8) -= 1;
            freeList->freeHead = pCurrent;
            // Update active list: skip the removed node
            if (pPrev == nullptr) {
                *ppActiveHead = pNext;
            } else {
                pPrev->next = pNext;
            }
            pCurrent = pNext; // continue with next, pPrev unchanged
        } else {
            pPrev = pCurrent;
            pCurrent = pNext;
        }
    }
}