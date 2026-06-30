// FUNC_NAME: GameManager::shutdown
void __thiscall GameManager::shutdown(GameManager* this)
{
    // Set vtable for this class (offset 0x0)
    this->vtable = &GameManager_vtable;

    // Set secondary vtable (offset +0xC) - likely for a second base
    this->secondaryVtable = &SecondaryBase_vtable;

    // Call initialization function with global data
    someInitFunction(&g_GlobalData);  // DAT_01206a20

    // Release managed object at offset +0x30 if it exists
    if (this->managedObject != 0) {
        releaseManagedObject(this->managedObject);  // FUN_009c8f10
    }

    // Update secondary vtable to another base (e.g., for destruction chain)
    this->secondaryVtable = &AnotherBase_vtable;

    // Reset global flag
    g_GameActive = 0;  // DAT_01129880

    // Call base class deinitialization
    baseClassCleanup();  // FUN_004083d0
}