// FUNC_NAME: setGameplayInputMode
void setGameplayInputMode(int inputContext)
{
    int inputMode;
    int gameState;
    int actionMapFlags;

    // Map input context to input mode ID (8,9,10,11)
    switch (inputContext)
    {
    case 1:
        inputMode = 9;
        break;
    case 2:
        inputMode = 10;
        break;
    case 3:
        inputMode = 11;
        break;
    default:
        inputMode = 8;
        break;
    }

    // Clear current input state
    clearInputState(0); // FUN_0081ebb0(0)

    gameState = 0;
    if (gGameManager != 0) // DAT_01129914 likely pointer to GodfatherGameManager
    {
        gameState = *(int *)(gGameManager + 0xC8); // +0xC8: e.g., GodfatherGameManager::gameState
    }

    // Choose action map flags based on current game state
    switch (gameState)
    {
    case 3: // Combat? or some state
        actionMapFlags = 4;
        break;
    case 1: // Free roam?
        actionMapFlags = 8;
        break;
    case 6: // Driving?
        actionMapFlags = 0x10;
        break;
    case 4: // Mission?
        actionMapFlags = 0x20;
        break;
    case 5: // Cutscene?
        actionMapFlags = 0x40;
        break;
    case 2: // Menu?
        actionMapFlags = 0x80;
        break;
    default:
        actionMapFlags = 0;
        break;
    }

    setInputActionMap(actionMapFlags, inputMode); // FUN_0081ef50(flags, inputMode)
}