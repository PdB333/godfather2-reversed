// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x005e1ca0
// Constructor for the main Godfather 2 game manager singleton.
// Initializes the vtable, calls a sub-initializer 5 times (likely for family/player slots),
// and sets default values for various member fields.

void GodfatherGameManager::GodfatherGameManager()
{
    // Store this as the global singleton reference.
    g_pGodfatherGameManager = this;

    // Set vtable (points to static table at 0x00e3f470).
    this->vtable = &GodfatherGameManager_vtable;

    // Initialize 5 subsystems (e.g., family slots, player slots, etc.)
    int subSystemCount = 4; // loop runs 5 times (4,3,2,1,0)
    do {
        initializeSubsystem(); // FUN_005e8140
        subSystemCount--;
    } while (subSystemCount >= 0);

    // Zero out several fields (likely flags, counters, or state arrays).
    // Offsets are relative to 'this'.
    this->field_0x5ce = 0;   // +0x5ce
    this->field_0x5cf = 0;   // +0x5cf
    this->field_0x5d0 = 0;   // +0x5d0
    *(byte *)&this->field_0x5d1 = 0; // +0x5d1 (1-byte)

    // Set default values for two more fields.
    this->field_0x5d2 = 1;   // +0x5d2
    this->field_0x5d3 = 5;   // +0x5d3
}