// FUNC_NAME: UIManager::handleStateTransition
void UIManager::handleStateTransition(int stateAction)
{
    int newDesiredState = 0; // local 4 (iVar1)
    int currentScreenMode = g_currentScreenMode; // unaff_ESI (global)
    int gameState = g_gameState; // DAT_0112537c

    // Skip state processing if in gameplay states (3 =? , 4 =?)
    if (gameState != 3 && gameState != 4)
    {
        if (currentScreenMode == 0)
        {
            newDesiredState = 0;
        }
        else if (stateAction == 0)
        {
            newDesiredState = 1;
        }
        else
        {
            // For states 2,5,6 (menus/paused?), skip transition
            if (gameState == 2 || gameState == 5 || gameState == 6)
                goto cleanup;

            newDesiredState = 2;
        }

        // If the desired state differs from current game state, apply transition
        if (gameState != newDesiredState)
        {
            FUN_0053b1e0(g_stateDataPtr); // DAT_01125380 -> pointer to state data
        }
    }

cleanup:
    // Release UI elements associated with the current index (g_currentIndex = DAT_01125389)
    // Each element array has stride 0x3c (60 bytes)
    if (*(int *)((char *)g_uiElementArray1 + (uint)g_currentIndex * 0x3c) != 0) // DAT_01125498
    {
        FUN_006063b0(); // releaseFirstUIElement
    }
    if (*(int *)((char *)g_uiElementArray2 + (uint)g_currentIndex * 0x3c) != 0) // DAT_0112549c
    {
        FUN_006063b0(); // releaseSecondUIElement
    }
}