// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, byte constructionFlags) {
    // Dereference the second vtable pointer (+0x10) to get a constructor function for base class/interface
    // param_1[4] is likely a pointer to a secondary vtable or interface table
    auto* baseConstructor = *(void (__thiscall**)(void))(this->_secondaryVTable + 4);  // +0x10 + 4
    this->_vtable = &PTR_FUN_00e3f2e0;   // Set primary vtable (base class)
    baseConstructor();                     // Call base class constructor via vtable
    FUN_005de2f0();                        // Initialize subsystem A (unknown)
    this->_secondaryVTable = &PTR_FUN_00e3f2e8;   // Set secondary vtable (derived class)
    FUN_004de130();                        // Initialize subsystem B (unknown)
    this->_vtable = &PTR_LAB_00e3f2e4;     // Override primary vtable (possibly final vtable for this class)
    g_gameManagerInitialized = 0;          // Clear global initialization flag
    if ((constructionFlags & 1) != 0) {
        FUN_009c8eb0(this);                // Conditional cleanup/destruction (indicates constructor failure handling)
    }
    return this;
}