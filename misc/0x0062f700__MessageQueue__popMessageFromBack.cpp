// FUNC_NAME: MessageQueue::popMessageFromBack
void MessageQueue::popMessageFromBack(int this_ptr)
{
    int* elementType;
    int* pCurrent;
    int* pDest;
    int* pSrc;
    
    // Check if queue is empty; if not, return
    if (FUN_0062f5c0(this_ptr) >= 0) {
        return;
    }
    
    // Get pointer to the element about to be removed (at current-8)
    int* pCurrentPtr = *(int**)(this_ptr + 8);
    elementType = (int*)(pCurrentPtr - 1); // pCurrent - 8 bytes (2 ints)
    if (elementType != (int*)0x0 && (*elementType == 3 || *elementType == 4)) {
        // Lock the queue (probably mutex)
        FUN_00627b40();
        
        // Shift elements forward to fill the gap left by removal
        pCurrent = *(int**)(this_ptr + 8);
        for (pDest = pCurrent; pCurrent - 1 < pDest; pDest -= 2) {
            *pDest = pDest[-2];
            pDest[1] = pDest[-1];
        }
        
        // Copy the last element (which was shifted) to the freed slot
        pSrc = *(int**)(this_ptr + 8);
        pCurrent[-1] = *pSrc;
        pCurrent[0] = pSrc[1];
        
        // Check if queue capacity needs to be expanded
        int* capacityInfo = *(int**)(this_ptr + 0x10);
        if (*(uint*)(capacityInfo + 0x20) <= *(uint*)(capacityInfo + 0x24)) {
            // Expand queue (reallocate)
            FUN_00627360();
        }
        
        // Notify that element at index ((current - base) / 8 - 1) has been removed
        int base = *(int*)(this_ptr + 0xc);
        int index = ((pCurrent - base) >> 3) - 1;
        FUN_006343b0(this_ptr, 2, index);
        
        // Move current pointer back by one element (8 bytes)
        *(int*)(this_ptr + 8) = (int)(pCurrent - 1);
    }
    
    // Unlock the queue
    FUN_006338a0();
    return;
}