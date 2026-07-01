// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Call base class constructor (likely EARSObject or Framework::Object)
    BaseObject::constructor((BaseObject*)this);

    // Set vtable pointer for the main class at offset 0x00
    this->vtable = &VTable_GodfatherGameManager;

    // Set a second vtable pointer (interface) at offset 0x10
    this->interfaceVtable = &VTable_GodfatherGameManager_Interface;

    // Override the vtable pointer at offset 0x4C (set by base constructor) with derived class table
    this->field_0x4C = &VTable_GodfatherGameManager_Override;

    // Initialize field at offset 0x50 to 0
    this->field_0x50 = 0;

    // Store this instance in the global singleton pointer
    g_pGodfatherGameManager = this;
}