// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Call base initialization with some magic ID and size?
    EngineInit(0xcffc631f, 8);

    // Set vtable for secondary base class at offset +0x148
    this->field_0x148 = &g_vtable_SecondBaseA;

    // Store global reference to this instance
    g_pGameManager = this;

    // OR in some flags at offset +0xFC (likely bitmask for state/subsystem flags)
    this->field_0xFC |= 0xC18;

    // Set primary vtable at offset +0x0
    this->vtable = &g_vtable_GodfatherGameManager;

    // Set vtable for secondary base class at offset +0x3C
    this->field_0x3C = &g_vtable_SecondBaseB;

    // Set vtable for secondary base class at offset +0x48
    this->field_0x48 = &g_vtable_SecondBaseC;

    // Override secondary base class vtable at offset +0x148 with a different one
    this->field_0x148 = &g_vtable_SecondBaseD;
}