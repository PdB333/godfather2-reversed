// FUNC_NAME: PoolManager::claimSlot
void __fastcall PoolManager::claimSlot(int thisPtr) {
    // thisPtr: object with a FreeListManager pointer at +0x5C
    int *freeListMgr = *(int **)(thisPtr + 0x5C);
    int slotId = ::getNextFreeSlot();  // FUN_00777310 – returns a free slot index
    if (slotId != 0) {
        int *currentSlot = freeListMgr + 0x1D3;  // offset 0x74C (0x1D3 * 4)
        int currentVal = *currentSlot;
        if (currentVal == 0 || currentVal == 0x48 || (currentVal - 0x48) != slotId) {
            // Reset the current slot token and call virtual "onSlotChange" via vtable+0x260
            (*(void (**)(void))(*freeListMgr + 0x260))();  // virtual function
            int newVal = slotId + 0x48;
            if (*currentSlot != newVal) {
                if (*currentSlot != 0) {
                    ::listRemoveEntry(currentSlot);  // FUN_004daf90 – remove old from list
                }
                *currentSlot = newVal;
                if (newVal != 0) {
                    freeListMgr[0x1D4] = *(int *)(slotId + 0x4C);   // store current list head
                    *(int **)(slotId + 0x4C) = currentSlot;          // link new slot as list head
                }
            }
        }
    }
}