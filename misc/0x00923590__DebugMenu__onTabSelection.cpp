// FUNC_NAME: DebugMenu::onTabSelection
void __fastcall DebugMenu::onTabSelection(DebugMenu* this)
{
    int tabIndex = *(int*)((char*)this + 0x58); // +0x58: current tab index
    if (tabIndex == 0) {
        createDebugSubmenu("InitBasicsMenu", 0, &gDebugMenu, 0);
    } else if (tabIndex == 1) {
        createDebugSubmenu("InitAttacksMenu", 0, &gDebugMenu, 0);
    } else if (tabIndex == 2) {
        createDebugSubmenu("InitInteractionMenu", 0, &gDebugMenu, 0);
    } else if (tabIndex == 3) {
        createDebugSubmenu("InitDrivingMenu", 0, &gDebugMenu, 0);
    } else if (tabIndex == 4) {
        createDebugSubmenu("InitDonControlMenu", 0, &gDebugMenu, 0);
    }
}