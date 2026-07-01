//FUNC_NAME: GameStateManager::processStateChange
// Address: 0x0091e7a0
// Role: Dispatches state-specific handlers based on current game state ID.
// Compares param_1 with main menu and gameplay state IDs, then switches on other known states.

void GameStateManager::processStateChange(int stateId)
{
    int mainMenuStateId = getMainMenuStateId();   // FUN_00466840
    if (stateId == mainMenuStateId) {
        handleMainMenuState();   // FUN_0091e630
        return;
    }

    int gameplayStateId = getGameplayStateId();   // FUN_00466860
    if (stateId == gameplayStateId) {
        handleGameplayState();   // FUN_00919730
        return;
    }

    switch (stateId) {
    case 2:
        handleState2();   // FUN_0091dd10
        break;
    case 3:
    case 6:
        handleState3or6();   // FUN_0091de50
        break;
    case 4:
        handleState4();   // FUN_0091e110
        break;
    case 5:
    case 7:
        handleState5or7();   // FUN_0091dfb0
        break;
    case 8:
        handleState8();   // FUN_0091da90
        break;
    case 9:
        handleState9();   // FUN_0091db80
        break;
    case 10:
        handleState10();   // FUN_0091dca0
        break;
    case 12:
        handleState12();   // FUN_00919810
        break;
    }
}