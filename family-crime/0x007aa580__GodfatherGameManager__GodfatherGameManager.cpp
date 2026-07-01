// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x007aa580
// Role: Constructor for the main game manager. Initializes vtables, calls base initialization, and sets a global flag.

void __thiscall GodfatherGameManager::GodfatherGameManager(void) {
    // Set the primary vtable (offset 0x00) to the derived class vtable
    this->vtable = (void*)&PTR_FUN_00d6b92c; // +0x00: primary vtable

    // Set the secondary vtable (offset 0x0C) to the base class vtable
    this->secondaryVtable = (void*)&PTR_LAB_00d6b928; // +0x0C: base class vtable pointer

    // Initialize base subsystem using global data
    initBaseSubsystem(&g_globalData); // FUN_004086d0: likely initializes global state

    // Restore the secondary vtable to the derived class's vtable
    this->secondaryVtable = (void*)&PTR_LAB_00d6b924; // +0x0C: derived class vtable pointer

    // Clear the global initialization flag
    g_bInitialized = 0; // DAT_01129954: indicates if manager is fully initialized

    // Finalize construction
    finalizeConstruction(); // FUN_004083d0: likely completes initialization
}