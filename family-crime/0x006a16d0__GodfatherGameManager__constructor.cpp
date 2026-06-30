// FUNC_NAME: GodfatherGameManager::constructor
// 0x006a16d0 - Constructor for the GodfatherGameManager singleton.
// Sets the global instance pointer, initializes the vtable, and performs internal setup.
GodfatherGameManager* __thiscall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Log with severity 6; DAT_00d5c454 is likely a static debug string
    debugPrint(6, DAT_00d5c454);

    // Store this instance as the global singleton (DAT_01129bb8)
    g_pGodfatherGameManager = this;

    // Assign the vtable (points to PTR_FUN_00d5d094)
    this->vtable = &GodfatherGameManager_vtable;

    // Call internal initialization (FUN_006a0840)
    this->internalInit();

    return this;
}