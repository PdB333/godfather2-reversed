// FUNC_NAME: MenuManager::setMenuVisibility
void __thiscall MenuManager::setMenuVisibility(int thisPtr, char show, char menuType)
{
    int *vtablePtr;

    // Store the show flag at offset +500 (0x1F4)
    *(char *)(thisPtr + 500) = show;
    // Set a bool at +0x144 to indicate if we are hiding (show == 0)
    *(bool *)(thisPtr + 0x144) = (show == '\0');
    // Set global input manager's state to -1 (likely disable input)
    *(int *)(g_inputManager + 0x34) = -1;

    if (show == '\0') {
        // Hiding menu
        *(char *)(thisPtr + 500) = 0; // redundant, already set
        // Clear global UI manager's active flag at +0xD3
        *(char *)(g_uiManager + 0xD3) = 0;
        // Call function to deactivate menu (0 = hide)
        setMenuActive(0);
        // Store menu type at +0x220
        *(char *)(thisPtr + 0x220) = menuType;
        // Call function to set submenu state (0, menuType == 0)
        setSubMenuState(0, (menuType == '\0'));
        return;
    }

    // Showing menu
    *(char *)(thisPtr + 500) = 1;
    if (menuType != '\0') {
        // Specific menu type (e.g., Don Control)
        *(char *)(g_uiManager + 0xD3) = 1;
        setMenuActive(1);
        hideCursor();
        vtablePtr = g_someManager;
        // Disable input
        setInputBlocked(0);
        // Call virtual function at offset 0x28 on g_someManager
        (**(code **)(*vtablePtr + 0x28))();
        return;
    }
    // Default menu type
    *(char *)(g_uiManager + 0xD3) = 1;
    setMenuActive(1);
    hideCursor();
    openMainMenu();
    return;
}