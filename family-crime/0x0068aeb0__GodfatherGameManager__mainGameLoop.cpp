// FUNC_NAME: GodfatherGameManager::mainGameLoop
void GodfatherGameManager::mainGameLoop(void)
{
    // Initialize memory manager and system
    FUN_00483a40(0); // likely memoryManager::init
    FUN_00609900(); // likely system::init

    // Check if game is already initialized
    int initResult = FUN_009c89c0(); // likely isGameInitialized
    if (initResult == 0) {
        // Initialize game systems
        int *gameSystems = (int *)FUN_009c9120(); // likely getGameSystems
        (**(code **)(*gameSystems + 8))(); // call init on game systems
        FUN_009c8f70(gameSystems); // likely releaseGameSystems
    }

    // Setup main loop state
    local_248 = 0;
    local_23c = 0;
    local_238 = 0;
    local_234 = 0;
    local_24c = FUN_009ce820; // likely mainLoopFunction
    local_244 = &LAB_009d0420; // likely frontendLoopFunction
    local_240 = &LAB_009d01a0; // likely initOnceLoopFunction

    // Register main loop callbacks
    FUN_004839f0(&local_24c); // likely registerLoopFunctions
    FUN_00412c50(); // likely initializeInput

    // Check if we can start the main loop
    char canStart = FUN_0068d010(); // likely canStartMainLoop
    if (canStart != '\0') {
        // Setup main loop data
        DAT_0112980c = appuStack_208; // likely mainLoopData
        appuStack_208[0] = &PTR_LAB_00d5a21c; // likely mainLoopVTable
        FUN_0068ac80(); // likely initializeMainLoopData

        // Register and start main loop
        uStack_22c = FUN_00683280("GameMainLoop"); // likely registerLoopName
        pppuVar8 = &ppuStack_230;
        ppuStack_230 = &PTR_FUN_00d5a1f8; // likely gameMainLoopVTable
        uStack_228 = 0;
        uStack_224 = 0;
        uStack_220 = 0;
        uStack_21c = 0;
        uStack_218 = 0;
        uStack_214 = 0;
        uStack_210 = 0;
        uStack_20c = 0;

        uVar6 = FUN_00683280("InitOnceMainLoop"); // likely registerLoopName
        FUN_00683360(uVar6, pppuVar8); // likely startLoop

        uVar6 = FUN_00683280("GameMainLoop"); // likely registerLoopName
        FUN_0067c390(uVar6); // likely registerGameLoop

        puVar9 = auStack_150;
        uVar6 = FUN_00683280("GameMainLoop"); // likely registerLoopName
        FUN_00683360(uVar6, puVar9); // likely startLoop

        uVar6 = FUN_00683280("GameMainLoop"); // likely registerLoopName
        FUN_0067c590(uVar6); // likely registerFrontendLoop

        puVar9 = auStack_17c;
        uVar6 = FUN_00683280("FrontendMainLoop"); // likely registerLoopName
        FUN_00683360(uVar6, puVar9); // likely startLoop

        uVar6 = FUN_00683280("InitOnceMainLoop"); // likely registerLoopName
        FUN_006834d0(uVar6); // likely finalizeLoop

        // Main loop
        do {
            char shouldContinue = FUN_00439fa0(); // likely shouldContinueLoop
            if (shouldContinue == '\0') {
                local_24c = (code *)0x0;
                FUN_00ab4b40(&local_24c); // likely exitLoop
            } else {
                cStack_24d = FUN_00683450(); // likely processLoop
            }

            // Handle state changes
            if (DAT_01129a70 != '\0') { // likely stateChangePending
                if (DAT_01129a71 == '\0') { // likely stateChangeInProgress
                    DAT_01129a71 = '\x01'; // set stateChangeInProgress
                    FUN_0060b610(0); // likely handleStateChange

                    ppuVar1 = DAT_0112980c[1]; // likely previousLoopData
                    FUN_0040d790(0); // likely cleanupState
                    FUN_0040eaa0(1); // likely setupNewState

                    if (DAT_01129a74 != (int *)0x0) { // likely stateChangeCallback
                        (**(code **)(*DAT_01129a74 + 0x2c))(); // call stateChangeCallback
                    }

                    uVar6 = FUN_00683280("GameMainLoop"); // likely registerLoopName
                    ppuVar7 = (undefined **)FUN_006833d0(uVar6); // likely getCurrentLoop
                    if (ppuVar1 != ppuVar7) {
                        uVar6 = FUN_00683280("FrontendMainLoop"); // likely registerLoopName
                        ppuVar7 = (undefined **)FUN_006833d0(uVar6); // likely getCurrentLoop
                        if (ppuVar1 == ppuVar7) {
                            FUN_0067c770(); // likely handleFrontendTransition
                        }
                    }
                }
                DAT_01129a70 = '\0'; // clear stateChangePending
            }
        } while (cStack_24d != '\0');

        // Cleanup and exit
        FUN_00607c30(); // likely cleanupMainLoop
        __exit(0);
    }

    __exit(0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
}