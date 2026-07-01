// FUNC_NAME: GameManager::processPauseCommand
void __thiscall GameManager::processPauseCommand(int this, uint param_2, void* context)
{
    int gameState;
    bool isPaused;
    bool isCutsceneActive;

    gameState = getCurrentGameState();  // FUN_00791750
    if (gameState < 3) {
        // In early game states (tutorial, menu, etc.)
        isPaused = isContextPaused(context);  // FUN_006b2190
        if (isPaused) {
            resumeContext(context);  // FUN_006b6560
            return;
        }
        freezeContext(context);  // FUN_006b3c60
        setPauseFlag(0);  // FUN_00790d30
        clearSomeState(0);  // FUN_00790110
        isCutsceneActive = isCutscenePlaying();  // FUN_00791230
        if (isCutsceneActive) {
            handleCutscenePause(context);  // FUN_00792d80
            return;
        }
    }
    else {
        // In gameplay states (state >= 3)
        freezeContext(context);  // FUN_006b3c60
        if (((*(uint*)(context + 0x5c) >> 0x1d & 1) != 0) && (*(int*)(this + 0x54) == 0x637b907)) {
            handleSpecialPause(context);  // FUN_008c1190
            return;
        }
        handleDefaultPause(context);  // FUN_008bf340
    }
    return;
}