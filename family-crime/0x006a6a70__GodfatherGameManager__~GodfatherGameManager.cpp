// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Function address: 0x006a6a70
// Destructor for the main game manager. Cleans up large arrays of pointers and shuts down subsystems.
void __fastcall GodfatherGameManager::~GodfatherGameManager() {
    // Set vtable to destructor-specific table (prevents virtual calls during destruction)
    this->vtable = (GodfatherGameManager_vtable*)0x00d5d7a8;           // *param_1 = &PTR_FUN_00d5d7a8
    this->baseVtable = (BaseClass_vtable*)0x00d5d7a4;                 // param_1[3] = &PTR_LAB_00d5d7a4

    // Call internal shutdown (likely releases resources managed by the engine)
    this->shutdown();                                                  // FUN_006a61d0

    // Free singleton-level pointers
    if (this->somePtr0) {                                              // param_1[0x1a5] (byte offset 0x694)
        deleteSinglePointer(&this->somePtr0);                          // FUN_004daf90(param_1 + 0x1a5)
    }
    if (this->somePtr1) {                                              // param_1[0x1a3] (byte offset 0x68C)
        deleteSinglePointer(&this->somePtr1);                          // FUN_004daf90(param_1 + 0x1a3)
    }

    // Free an array of 8 pointers (each 0x28 bytes apart)
    int i = 7;
    void** ptrArray = &this->array_8_start;                           // param_1 + 0x19f (byte offset 0x67C)
    do {
        void** current = ptrArray - (7 - i) * 10;                     // Subtract 10 elements (0x28 bytes) per iteration
        if (*current) {
            deleteSinglePointer(current);                              // FUN_004daf90(current)
        }
        i--;
    } while (i >= 0);

    // Free a single pointer
    if (this->anotherPtr) {                                            // param_1[0x149] (byte offset 0x524)
        deleteSinglePointer(&this->anotherPtr);                        // FUN_004daf90(param_1 + 0x149)
    }

    // Free an array of 32 pointers (each 0x28 bytes apart)
    i = 0x1F;
    void** ptrArray2 = &this->anotherPtr;                             // param_1 + 0x149 (byte offset 0x524)
    do {
        void** current = ptrArray2 - (0x1F - i) * 10;                 // Subtract 10 elements each iteration
        if (*current) {
            deleteSinglePointer(current);                              // FUN_004daf90(current)
        }
        i--;
    } while (i >= 0);

    // Switch vtable to base class destructor vtable
    this->baseVtable = (BaseClass_vtable*)0x00d5d7a0;                 // param_1[3] = &PTR_LAB_00d5d7a0

    // Clear global singleton flag
    g_GodfatherGameManagerExists = false;                              // DAT_011299b0 = 0

    // Call base class destructor
    this->callBaseDestructor();                                        // FUN_004083d0
}