// FUNC_NAME: GodfatherGameManager::shutdown
// Function at 0x006a61d0: Cleanup/shutdown for the main game manager (GodfatherGameManager).
// Handles static data clearing, per-slot resource freeing, and subsystem shutdown.
// Observations:
//   - Clears several global static data (DAT_01206794 etc.) via FUN_004086d0 (likely deinit).
//   - Iterates over 8 slots (each 0x28 bytes) starting at offset +0x53c. Each slot has a pointer at offset +0x4 (relative to slot start) and a preceding int at -0x4.
//   - Resets the preceding int to 0, frees the pointed-to resource if non-null.
//   - Also zeros two fields at offsets +0x558 and +0x55c in a different array indexed by the value at +0x678 (probably current active slot index).
//   - Calls FUN_006a5740 (likely a subsystem shutdown).
//   - Frees two pointers at +0x68c and +0x694.

// Assume the following named functions:
//   void __fastcall globalStaticDeinit(void* addr);  // FUN_004086d0
//   void __fastcall operatorDelete(void* ptr);       // FUN_004daf90
//   void __cdecl subsystemShutdown();                // FUN_006a5740

void __fastcall GodfatherGameManager::shutdown(int thisObj)
{
    int i;
    int* slotPtr;
    int activeSlotIndex;

    // Clear global static data (likely singleton/database objects)
    globalStaticDeinit(&g_StaticData0);  // DAT_01206794
    globalStaticDeinit(&g_StaticData1);  // DAT_0120678c
    globalStaticDeinit(&g_StaticData2);  // DAT_01206780
    globalStaticDeinit(&g_StaticData3);  // DAT_012067b4
    globalStaticDeinit(&g_StaticData4);  // DAT_012069c4

    // Start at the first slot's second field (offset +0x53c).
    // Each slot is 0x28 bytes (10 ints). The loop processes 8 slots.
    slotPtr = (int*)(thisObj + 0x53c);
    for (i = 0; i < 8; i++)
    {
        // Clear the field immediately before this slot pointer (slot->field0)
        slotPtr[-1] = 0;

        // If the slot has an allocated resource pointer (slot->resourcePtr),
        // free it and null it out.
        if (*slotPtr != 0)
        {
            operatorDelete((void*)*slotPtr);  // FUN_004daf90
            *slotPtr = 0;
        }

        // Note: The original loop also zeros two fields in a *different* array
        // using a fixed index (thisObj->activeSlotIndex) each iteration.
        // This may be a compiler artifact or intentional redundant zeroing.
        activeSlotIndex = *(int*)(thisObj + 0x678);
        *(int*)(thisObj + 0x558 + activeSlotIndex * 0x28) = 0;  // slotArray2->fieldX
        *(int*)(thisObj + 0x55c + activeSlotIndex * 0x28) = 0;  // slotArray2->fieldY

        // Move to the next slot (each slot advances by 10 ints = 40 bytes)
        slotPtr += 10;
    }

    // Shutdown an additional subsystem
    subsystemShutdown();  // FUN_006a5740

    // Free two more managed resources
    if (*(int*)(thisObj + 0x68c) != 0)
    {
        operatorDelete(*(void**)(thisObj + 0x68c));
        *(int*)(thisObj + 0x68c) = 0;
    }
    if (*(int*)(thisObj + 0x694) != 0)
    {
        operatorDelete(*(void**)(thisObj + 0x694));
        *(int*)(thisObj + 0x694) = 0;
    }
}