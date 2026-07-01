// FUNC_NAME: GameFlowManager::updateFlow
void __fastcall GameFlowManager::updateFlow(GameFlowManager* this) {
    if (gFlowUpdateInterval <= *(float*)((int)this + 0xA8)) {
        gFlowFlags = gFlowFlags & 0xFFFFFBFF;
        switch (*(int*)((int)this + 0x6C)) {
        case 0: // INIT
            introUpdate();
            resetPointer(&gSomeGlobal0, 0);
            return;
        case 1: // MAIN_MENU
            gFlowFlags = gFlowFlags | 0x400;
            (*(code**)(**(int**)gSomeVTable1 + 0x2C))(); // call via vtable
            mainMenuUpdate();
            return;
        case 2: // LOADING_GAME
            if (*(int*)(*(int*)gSomeGlobal1 + 0x2C) != 0) {
                cleanupLoadingResources();
            }
            gCurrentScreenId = 0x16;
            setScreenState(0);
            resetPointer(&gSomeGlobal0, 0);
            return;
        case 3: // OPTIONS_MENU
            if (isDialogActive() != 0) {
                (*(code**)(**(int**)gSomeVTable2 + 4))(); // call via vtable
            }
            gCurrentScreenId = 0x12;
            setScreenState(0);
            resetPointer(&gSomeGlobal0, 0);
            resetPointer(&gSomeGlobal1, 0);
            resetPointer(&gSomeGlobal2, 0);
            return;
        case 4: // CREDITS
            if (isCreditsFinished() != 0) {
                gCurrentScreenId = 0x1D;
                setScreenState(0);
                resetPointer(&gSomeGlobal0, 0);
                return;
            }
            *(char*)((int)this + 0xB4) = 1;
            showCredits();
            resetPointer(&gSomeGlobal0, 0);
            return;
        case 5: // CONTROLS_MENU
            if (isDialogActive() != 0) {
                (*(code**)(**(int**)gSomeVTable2 + 4))();
            }
            gCurrentScreenId = 0x13;
            setScreenState(0);
            resetPointer(&gSomeGlobal0, 0);
            resetPointer(&gSomeGlobal3, 0);
            return;
        case 6: // LOADING_SCREEN
            gCurrentScreenId = 0x14;
            *(float*)((int)this + 0xA8) = 0.0f;
            setScreenState(0);
            break;
        case 7: // EXIT_TO_MAIN_MENU
            cleanupMultiplayer();
            cleanupControllers();
            releaseResource(&gSomeResource);
            resetSoundEngine();
            gCurrentScreenId = 0x20;
            setScreenState(0);
            resetPointer(&gSomeGlobal0, 0);
            resetPointer(&gSomeGlobal2, 0);
            return;
        case 8: // IDLE
            skipScreenTransition();
            break;
        default:
            goto END;
        }
        resetPointer(&gSomeGlobal0, 0);
        resetPointer(&gSomeGlobal2, 0);
    }
END:
    return;
}