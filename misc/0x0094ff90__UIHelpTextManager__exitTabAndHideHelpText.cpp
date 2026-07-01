//FUNC_NAME: UIHelpTextManager::exitTabAndHideHelpText

void __fastcall UIHelpTextManager::exitTabAndHideHelpText(int this)
{
    int *vtablePtr;

    vtablePtr = g_pHelpTextVTable; // DAT_011304fc
    if (*(int *)(this + 0x54) == 0 || (vtablePtr = g_pAltVTable, *(int *)(this + 0x54) == 1)) {
        // Call virtual function at offset 0x2c (likely onExitTab or onHideHelpText)
        (*(void (__thiscall **)(int))(*(int *)vtablePtr + 0x2c))(this);
    }

    // Send "ExitTab" event
    EventManager::triggerEvent("ExitTab", 0, &g_EventData, 0); // FUN_005a04a0

    *(int *)(this + 0x50) = 0; // +0x50: some state flag
    *(int *)(this + 0x54) = 0; // +0x54: tab/help state

    // Send "HideHelpText" event
    EventManager::triggerEvent("HideHelpText", 0, &g_EventData, 0); // FUN_005a04a0

    this += 0x14; // +0x14: pointer to a timer/callback list
    // Remove various timers/callbacks
    TimerManager::removeTimer(this, &g_TimerExitTab, 0);       // FUN_005c0d50
    TimerManager::removeTimer(this, &g_TimerHelpTextShow, 0);  // FUN_005c0d50
    TimerManager::removeTimer(this, &g_TimerHelpTextHide, 0);  // FUN_005c0d50
    TimerManager::removeTimer(this, &g_TimerGeneric, 0);       // FUN_005c0d50
}