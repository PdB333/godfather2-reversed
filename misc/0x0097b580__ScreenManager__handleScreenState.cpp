// FUNC_NAME: ScreenManager::handleScreenState
// Function address: 0x0097b580
// Role: Processes screen state transitions (IDs: main menu, controls, gameplay, hide screen)
int __thiscall ScreenManager::handleScreenState(int screenId)
{
    int mainMenuId = getMainMenuId(); // FUN_00466840
    int controlsId = getControlsScreenId(); // FUN_00466860

    if (screenId == mainMenuId) 
    {
        if (*(int *)(this + 0x104) != 0)  // check some pending transition flag
        {
            executePendingTransition(); // FUN_0097e560
            return 0;
        }
    }
    else 
    {
        if (screenId == controlsId || screenId == 0) // 0 = no screen?
        {
            logMessage("PrepareToHideScreen", 0, &DAT_00d8f99c, 0); // FUN_005a04a0 (debug/log)
        }
        else 
        {
            if (screenId == 3) // some map/loading screen
            {
                showMapScreen(); // FUN_0097b4f0
                return 0;
            }
            if (screenId == 5) // gameplay screen
            {
                showGameplayScreen(); // FUN_00979da0
                return 0;
            }
        }
    }
    return 0;
}