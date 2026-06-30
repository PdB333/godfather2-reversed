// FUNC_NAME: GameStateManager::handleEvent
// 0x004e0210 - Processes game flow events and manages state transitions (splash/loading/main menu)
// Uses thread-local storage (FS:[0x2c]) to access global state machine pointer.
// State machine vtable at gStateMachine+0x14 is swapped to transition between states.
void GameStateManager::handleEvent(int *this) // this is pointer to event ID or object
{
    int *tlsPtr; // piVar3 - from TLS (Thread Local Storage)
    int result; // iVar1
    int *vtableSlot; // piVar2
    int eventId = *this; // Dereference this to get event type ID
    int someLocal; // local_c

    tlsPtr = *(int **)(__readfsdword(0x2c) + 0x28); // FS:[0x2c] -> TEB->ThreadLocalStoragePointer, then +0x28 to get a global or per-thread state pointer

    // Check event type by comparing to global DAT constants
    if (eventId == gEventId_Init) { // DAT_01206960
        result = GameStateManager::getInitialState(); // FUN_004e9fa0
        GameStateManager::setState(result); // FUN_004ea270
        // Conditionally exit if a certain flag is not set
        if (*(int *)((uint)(*(int *)(*tlsPtr + 0x34) != 0) * 0x98 + 4 + result) == 0) {
            return;
        }
    }
    else if (eventId == gEventId_ShowSplash) { // DAT_01206968
        vtableSlot = (int *)(gStateMachine + 0x14); // Get address of vtable pointer
        *(undefined4 **)(gStateMachine + 0x14) = &SPLASH_VTABLE; // PTR_LAB_01124a7c
        *vtableSlot = *vtableSlot + 4; // Increment vtable pointer? (likely a reference count or offset)
    }

    // Main state machine if global state > 3
    if (gMainState > 3) { // DAT_01194540
        if ((eventId == gEventId_LoadingProgress) || (eventId == gEventId_LoadingComplete)) { // DAT_012069d4/DAT_012069ec
            if (gMainState == 5) { // Loading phase
                GameStateManager::clearScreen(0); // FUN_004e3e80 with 0
                GameStateManager::renderFrame(gRenderDevice); // FUN_00519020
                gLoadingCounter--; // DAT_0119453c
                if (gLoadingCounter < 1) {
                    vtableSlot = (int *)(gStateMachine + 0x14);
                    *(undefined4 **)(gStateMachine + 0x14) = &MAINMENU_VTABLE; // PTR_LAB_01124a68
                    *vtableSlot = *vtableSlot + 4;
                    gMainState = 6; // Transition to main menu
                    return;
                }
            }
            else if ((gMainState != 6) && (gMainState == 7)) { // Active menu state
                someLocal = gLocalVarA; // DAT_012067e8
                if (eventId == gEventId_LoadingComplete) {
                    someLocal = gLocalVarB; // DAT_01206800
                }
                GameStateManager::clearScreen(someLocal); // FUN_004e3e80
                GameStateManager::postLoadProcess(someLocal, eventId == gEventId_LoadingComplete); // FUN_0051c710
                GameStateManager::renderFrame(gRenderDevice);
                if (eventId == gEventId_LoadingComplete) {
                    GameStateManager::handleCompleteLoading(); // FUN_00525b40
                } else {
                    GameStateManager::handleProgressLoading(); // FUN_00525b40 (same function but different context)
                }
            }
        }
        else {
            if (eventId == gEventId_Escape) { // DAT_01206980
                GameStateManager::handleEscape(); // FUN_0051c350
                return;
            }
            if (eventId == gEventId_Select) { // DAT_01206970
                GameStateManager::handleSelect(*(undefined4 *)(*tlsPtr + 0x24)); // FUN_0051c390
                return;
            }
        }
    }
    return;
}