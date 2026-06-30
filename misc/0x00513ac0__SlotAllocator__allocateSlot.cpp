// FUNC_NAME: SlotAllocator::allocateSlot
void SlotAllocator::allocateSlot(int* outHandle) {
    LPCRITICAL_SECTION criticalSection;
    int iVar1;
    int iVar2;
    int iVar3;
    int fsBase;

    iVar2 = s_globalManager;                     // DAT_0120541c - pointer to global manager
    criticalSection = *(LPCRITICAL_SECTION*)(s_globalManager + 0x1b8); // critical section at offset 0x1b8

    iVar3 = 0;
    if (criticalSection != NULL) {
        EnterCriticalSection(criticalSection);
        // The critical section debug info is abused for a counter increment/decrement (EA pattern)
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo->Type + 1);
    }

    iVar1 = allocateMemory(s_globalManager, 0x2a0); // FUN_00649040 - allocate 672 bytes
    if (iVar1 == 0) {
        if (criticalSection != NULL) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
        iVar2 = *(int*)(s_globalManager + 0x17c); // fallback to some alternate pointer
    } else {
        initializeAllocation(iVar1);              // FUN_006492f0 - calls constructor on the block
        iVar2 = *(int*)(iVar1 + 8);               // get pointer at offset +8 from allocated block
        if (criticalSection != NULL) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
    }

    if (iVar2 != 0) {
        iVar3 = iVar2 - s_globalBase;                    // offset from global base (DAT_01205410)
        // Access per-thread data via TLS (FS:[0x2c] is the thread-local data pointer)
        fsBase = *(int*)(*(int*)(__readfsdword(0x2c)) + 8); // double dereference to get thread-local array base
        int* slotArray = (int*)(fsBase + iVar3);        // base of 8 slots (each 0x50 bytes)
        // Zero out 8 slots starting at offset 0x50 in the thread-local structure
        slotArray[0x50/4] = 0;   // offset 0x50
        slotArray[0xa0/4] = 0;   // offset 0xa0
        slotArray[0xf0/4] = 0;   // offset 0xf0
        slotArray[0x140/4] = 0;  // offset 0x140
        slotArray[400/4] = 0;    // offset 0x190
        slotArray[0x1e0/4] = 0;  // offset 0x1e0
        slotArray[0x230/4] = 0;  // offset 0x230
        slotArray[0x280/4] = 0;  // offset 0x280
    }

    *outHandle = iVar3;         // store handle (offset index)
    outHandle[1] = 1;           // always set to 1 (success flag)
}