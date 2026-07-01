// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, int param2)
{
    // Call base class constructor (likely GameManager or EARSObject)
    GameManager::GameManager(param2);

    // Override base vtable with class-specific vtable
    this->vtable = &g_GodfatherGameManager_vtable; // offset +0x00, PTR_FUN_00d81140

    // Set handler/table pointers (overrides base values)
    this->handlerTable1 = &g_finalHandlerTable1; // offset +0x824, PTR_LAB_00d810f0
    this->handlerTable2 = &g_finalHandlerTable2; // offset +0x825, PTR_LAB_00d810ec

    // Zero out fields at +0x826 through +0x82b
    this->field_0x826 = 0;
    this->field_0x827 = 0;
    this->field_0x828 = 0;
    this->field_0x829 = 0;
    this->field_0x82a = 0;
    this->field_0x82b = 0;

    // Clear an array of 0x1a structures, each 12 bytes, starting at offset +0x82c
    for (int i = 0; i < 0x1a; i++)
    {
        this->largeArray[i].field0 = 0; // offset +0x82c + i*12
        this->largeArray[i].field4 = 0; // offset +0x82c + i*12 + 4
        this->largeArray[i].field8 = 0; // offset +0x82c + i*12 + 8
    }

    // Initialize counters/flags at large offsets
    this->someCounter = 0;  // offset +0x898
    this->someFlag1   = 0;  // offset +0x899
    this->someFlag2   = 0;  // offset +0x89a
    this->someByte    = 0;  // offset +0x89c

    // Global library initialization calls
    GlobalInitFunction();                            // FUN_00accc70
    InitializeGlobalStructure(&g_globalStruct1);     // FUN_00408680(&DAT_01222240)
    InitializeGlobalStructure(&g_globalStruct2);     // FUN_00408680(&DAT_01222250)

    // Set a control flag at offset +0x10 (bit 3)
    this->flags |= 8;

    // Register this instance as the global singleton
    g_pGodfatherGameManager = this; // DAT_01129828

    return this;
}