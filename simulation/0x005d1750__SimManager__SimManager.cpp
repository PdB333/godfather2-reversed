// FUNC_NAME: SimManager::SimManager
void __fastcall SimManager::SimManager(void* this) {
    // Set base vtable (likely from a base class)
    *(void**)this = &PTR_FUN_00e3edcc; // +0x00 vtable pointer (base)

    // Initialize an array of 192 sub-objects (e.g., SimNpc slots)
    int count = 0xbf; // 191
    do {
        // Call sub-object constructor for each element
        // The actual call passes the address of each sub-object in ECX (this pointer)
        FUN_005d2370(); // SubObject::SubObject() – initializes one element
        count--;
    } while (count >= 0);

    // Switch to derived vtable after base initialization
    *(void**)this = &PTR_LAB_00e3edd0; // +0x00 vtable pointer (derived)

    // Mark manager as initialized (or reset a global flag)
    DAT_012234f4 = 0; // g_simManagerInitialized = false
}