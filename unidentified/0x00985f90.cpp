// FUN_NAME: ActionManager::handleCommand

void ActionManager::handleCommand(int actionId)
{
    switch(actionId)
    {
        case 0: // Initialize
            FUN_005c3960();
            FUN_005c26d0();
            break;
        case 1: // Start
            FUN_005c3960();
            FUN_005c26d0();
            break;
        case 2: // Stop
            FUN_00985ec0();
            break;
        case 3: // Pause
            FUN_005c3960();
            FUN_005c26d0();
            break;
        case 4: // Save
            FUN_00985c70();
            break;
        case 5: // Load
            FUN_00985de0();
            break;
        case 6: // Reset
            FUN_00985d70();
            break;
    }
}