// Xbox PDB: EARS_Apt_UIBase_WaitForLoadSequence
// FUNC_NAME: UIManager::showBaseScreen
// Function address: 0x00911e00
// Checks if "basescreen" exists; if so, activates it and calls a virtual method at vtable offset 0x28.

bool __thiscall UIManager::showBaseScreen()
{
    // Check if the "basescreen" is registered in the screen manager
    if (FUN_005bd670("basescreen") != '\0') // likely screenExists("basescreen")
    {
        // Activate the screen with some global data (maybe a pointer to screen instance)
        FUN_0059e490("basescreen", &DAT_00e3c2bc); // likely activateScreen("basescreen", data)

        // Call a virtual function at offset 0x28 of the this->vtable
        // This could be something like onActivate() or performUpdate()
        (this->vtable[0x28 / 4])();  // vtable +0x28

        return true;
    }
    return false;
}