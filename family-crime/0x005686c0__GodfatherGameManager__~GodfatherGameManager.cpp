// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Address: 0x005686c0
// Role: Destructor for GodfatherGameManager singleton. Cleans up and clears global flag.

void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this) {
    // Set vtable to derived class vtable (or self) before destruction
    *(int**)this = &PTR_FUN_00e3aa80;
    
    // Check if a sub-object or flag at offset +0x0C (field[3]) is non-zero
    if (this->field_0x0C != 0) {
        // Call the destructor's helper function (likely base class destructor or cleanup)
        FUN_00568740();
    }
    
    // Reset vtable to base class vtable (or sentinel) after destruction
    *(int**)this = &PTR_LAB_00e3aad0;
    
    // Clear the global instance flag indicating this manager is no longer active
    DAT_012234e0 = 0;
}