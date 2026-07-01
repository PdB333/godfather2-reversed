// FUNC_NAME: OptionsMenu::initCurrentTab
void __fastcall OptionsMenu::initCurrentTab(OptionsMenu* thisPtr)
{
    int currentTabIndex = *(int*)((int)thisPtr + 0x58); // +0x58: current tab index (0=audio,1=video,2=advanced)

    if (currentTabIndex == 0)
    {
        // Audio tab
        FUN_005a04a0("InitAudioMenu", 0, &DAT_00d90fa8, 0);
        return;
    }
    if (currentTabIndex == 1)
    {
        // Video tab: compose resolution string
        int displayWidth = *(int*)((int)thisPtr + 0x114);   // +0x114: display width
        int displayHeight = *(int*)((int)thisPtr + 0x110);  // +0x110: display height
        int displayRefreshRate = *(int*)((int)thisPtr + 0x118); // +0x118: refresh rate
        _sprintf((char*)((int)thisPtr + 0xc4), "%d x %d @ %dHz", displayWidth, displayHeight, displayRefreshRate);
        FUN_005a04a0("InitVideoMenu", 0, &DAT_00d90fa8, 0);
        return;
    }
    if (currentTabIndex == 2)
    {
        // Advanced tab
        FUN_005a04a0("InitAdvancedMenu", 0, &DAT_00d90fa8, 0);
    }
    // No action for other values
}