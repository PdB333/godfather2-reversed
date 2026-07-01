// FUNC_NAME: OnlineMenuManager::showMapUnavailable
void OnlineMenuManager::showMapUnavailable()
{
    // Allocate a 0xF0-byte block (size of OnlinePopupDialog or similar)
    int menuData = reinterpret_cast<int>(MemoryManager::Allocate(0xF0));
    if (menuData != 0)
    {
        menuData = reinterpret_cast<int>(UIElement::init(0));
    }
    else
    {
        menuData = 0;
    }

    // Set the localized text string
    UIElement::SetText("$mp_online_menu_map_unavailable");

    // Write state/type at offset +0xC (likely eDialogType or eMenuState)
    *(int*)(menuData + 0xC) = 3;  // e.g., DIALOG_TYPE_INFORMATION or MENU_STATE_SHOW

    // Write a vtable pointer or callback function at offset +0x14
    *(void**)(menuData + 0x14) = reinterpret_cast<void*>(FUN_00982b30);  // Event handler or vtable

    // Display the dialog
    UIElement::Show();
}