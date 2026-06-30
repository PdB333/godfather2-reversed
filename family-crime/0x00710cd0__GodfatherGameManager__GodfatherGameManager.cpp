// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(void* thisPtr) {
    // Offset 0: Set vtable pointer to class virtual function table
    *(void**)thisPtr = &PTR_FUN_00d618f4;

    // Offsets 0x3C (0xF * 4) and 0x48 (0x12 * 4): Set additional function pointer tables
    *(void**)((uint32_t*)thisPtr + 0xF) = &PTR_LAB_00d618e4;
    *(void**)((uint32_t*)thisPtr + 0x12) = &PTR_LAB_00d618e0;

    // Initialize subobject at offset 0x50 (0x14 * 4) - two-phase construction
    FUN_004086d0((uint32_t*)thisPtr + 0x14);
    FUN_00408310((uint32_t*)thisPtr + 0x14);

    // Initialize subobject at offset 0x58 (0x16 * 4) - two-phase construction
    FUN_004086d0((uint32_t*)thisPtr + 0x16);
    FUN_00408310((uint32_t*)thisPtr + 0x16);

    // Global system initialization
    FUN_00710990();

    // Cleanup: if child pointer at offset 0x120 (0x48 * 4) is non-null, release it
    if (*(void**)((uint32_t*)thisPtr + 0x48) != nullptr) {
        FUN_004daf90(*(void**)((uint32_t*)thisPtr + 0x48));
    }

    // Dispatch: if pointer at offset 0x10C (0x43 * 4) is non-null, call function at offset 0x118 (0x46 * 4) with it
    if (*(void**)((uint32_t*)thisPtr + 0x43) != nullptr) {
        ((void (*)(void*))(*(void**)((uint32_t*)thisPtr + 0x46)))(*(void**)((uint32_t*)thisPtr + 0x43));
    }

    // Global finalization call
    FUN_0046c640();
}