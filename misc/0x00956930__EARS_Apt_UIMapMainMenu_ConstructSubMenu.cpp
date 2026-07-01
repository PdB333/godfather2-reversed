// Xbox PDB: EARS_Apt_UIMapMainMenu_ConstructSubMenu
// FUNC_NAME: MenuController::populateSubMenu
// Address: 0x00956930
// Role: Populates a submenu with options by resetting and adding options from the menu entry data.

void __thiscall MenuController::populateSubMenu(int subMenuIndex)
{
    // Get the pointer to the submenu entry for the given index
    // Offset +0x54: array of pointers to submenu entry objects
    SubMenuEntry* pEntry = *(SubMenuEntry**)(this + 0x54 + subMenuIndex * 4);

    // Call Lua command to reset the submenu (clear previous options)
    // DAT_00d8c174 and DAT_00e3d9a4 are constants (likely menu handle and submenu ID)
    callLuaMenuCommand("ResetSubMenu", 0, &DAT_00d8c174, 1, &DAT_00e3d9a4);

    // Number of options in this submenu, stored at offset +0x70
    int optionCount = *(int*)(this + 0x70);
    if (optionCount > 0)
    {
        char optionName[64];
        char optionDescription[64];

        for (int i = 0; i < optionCount; i++)
        {
            optionName[0] = '\0';
            optionDescription[0] = '\0';

            // Virtual function at vtable+0x7c: get the name of option i into buffer
            (*(void (__thiscall**)(int, char*, int))(*(int*)pEntry + 0x7c))(i, optionName, 0x40);
            // Virtual function at vtable+0x80: get the description of option i into buffer
            (*(void (__thiscall**)(int, char*, int))(*(int*)pEntry + 0x80))(i, optionDescription, 0x40);

            // Add the option to the Lua submenu
            callLuaMenuCommand("AddSubMenuOption", 0, &DAT_00d8c174, 2, optionName, optionDescription);
        }
    }
}