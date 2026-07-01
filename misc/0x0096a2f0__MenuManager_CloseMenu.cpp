// FUNC_NAME: MenuManager_CloseMenu
// Address: 0x0096a2f0
// Role: Closes the current menu, resetting selection and clearing UI state
void MenuManager_CloseMenu(void)
{
    // Deinitialize menu subcomponents
    menuCleanup();                             // FUN_0096a1e0

    // Reset menu mode to base state (0 = no menu)
    resetMenuState(0);                        // FUN_00970400(0)

    // Dispatch UI events to hide menu and unhighlight selection
    // DAT_00d8cdec likely points to the UI data block (e.g., WidgetData*)
    sendUIMessage("ShowMenu", 0, (UiData*)&DAT_00d8cdec, 0);           // FUN_005a04a0
    sendUIMessage("HighlightSelected", 0, (UiData*)&DAT_00d8cdec, 0); // FUN_005a04a0

    // Reset selected item index to invalid (-1)
    // DAT_0112b9b4 is probably the MenuManager singleton pointer
    // Offset +0x34: int selectedItemIndex (or highlighted slot)
    MenuManager* mgr = (MenuManager*)DAT_0112b9b4;
    mgr->selectedItemIndex = -1;               // *(undefined4 *)(DAT_0112b9b4 + 0x34) = 0xffffffff
}