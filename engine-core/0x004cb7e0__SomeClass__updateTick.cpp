// FUNC_NAME: SomeClass::updateTick
void SomeClass::updateTick() {
    // Global recursion counter increment/decrement
    extern int g_updateCounter; // _DAT_01205a30
    g_updateCounter++;

    // Probably a placeholder or network byte order conversion for something
    htonl(0);

    // Virtual call at +0xc (likely 'onUpdate' or similar)
    (this->*vtable[3])();  // vtable offset 0xc / 4 = 3

    // Check for active object from two sources
    int* activeObj = FUN_00655250(); // returns some object pointer or null
    if (activeObj == nullptr) {
        activeObj = FUN_00655130(); // second source
    }

    if (activeObj != nullptr) {
        // Call function with member at +0x1a4 and the object itself
        // +0x1a4 could be a member like 'callback' or 'state'
        FUN_006576b0(*(int*)((char*)activeObj + 0x1a4), activeObj);
    }

    g_updateCounter--;
}