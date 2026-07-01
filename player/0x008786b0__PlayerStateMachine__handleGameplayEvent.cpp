// FUNC_NAME: PlayerStateMachine::handleGameplayEvent
// Function at 0x008786b0 - Handles gameplay state transitions based on event type and player state
// EARS framework: Player state machine event handler

void __thiscall PlayerStateMachine::handleGameplayEvent(int this, int param2, undefined4 param3, undefined1 *outResult)
{
    undefined1 *pResult;
    char charResult;
    int stateType;
    int playerFlags;
    int tempVar;
    int *pData;

    // Initialize output
    pResult = outResult;
    *outResult = 0;

    // Check if game manager exists (global singleton reference)
    // DAT_012233a0 is likely gGameManager or global singleton pointer
    if (**(int **)(DAT_012233a0 + 4) == 0) {
        tempVar = 0;
    }
    else {
        tempVar = **(int **)(DAT_012233a0 + 4) + -0x1f30; // Offset to gameplay state manager
    }

    // Get event type identifier (0x55859efa is likely a hash/ID for a specific event)
    stateType = FUN_0084daa0(this, 0x55859efa);

    // Get current player state definition (through vtable at +0x7c0, offset 0x34)
    // param_1 + 0x7c0 points to state machine's current state object
    playerFlags = (**(code **)(**(int **)(this + 0x7c0) + 0x34))();

    if (stateType == 0) {
        // Handle specific state transitions when event type matches
        if (((*(int *)(playerFlags + 0x30) == 3) && (*(int *)(playerFlags + 4) != 0)) &&
            (*(int *)(playerFlags + 4) != 0x48)) {

            // Calculate base of state data (-0x48 adjustment for internal structure)
            if (*(int *)(playerFlags + 4) == 0) {
                pData = (int *)0x0;
            }
            else {
                pData = (int *)(*(int *)(playerFlags + 4) + -0x48);
            }

            // Check if state allows transition via virtual function at vtable+0x10
            outResult = (undefined1 *)0x0;
            charResult = (**(code **)(*pData + 0x10))(0xa5975eb2, &outResult);

            // Process state transition conditions
            if (((charResult != '\0') && (param2 != 0)) && (param2 != this)) {
                // Check bit 0x15 (bit 21) of flags at +0xc88
                // This likely indicates a special state flag
                if ((*(uint *)(this + 0xc88) >> 0x15 & 1) != 0) {
                    FUN_0079ee00(unaff_EBX, unaff_retaddr); // Likely triggers state transition animation
                    *pResult = 1; // Signal success
                    return;
                }

                // Check bit 0x16 (bit 22) and compare player ID at +0xb90 with game manager state
                if ((((*(uint *)(this + 0xc88) >> 0x16 & 1) != 0) && (tempVar != 0)) &&
                   (*(int *)(this + 0xb90) != *(int *)(tempVar + 0x1ed4))) {
                    FUN_0079ee40(unaff_EBX, unaff_retaddr); // Different transition handling
                }
            }
        }
    }
    else {
        // Alternative event handling path - check global state manager
        tempVar = FUN_00806440(); // Get global gameplay state type (0,1,2,3 likely: menu, gameplay, pause, etc)
        if (tempVar == 2) {
            // State 2 - likely Pause or Menu state
            FUN_0079ee00(param2, param3);
            *pResult = 1;
            return;
        }
        if (tempVar == 3) {
            // State 3 - likely Cutscene or Special state
            FUN_0079ee40(param2, param3);
            return;
        }
    }
    return;
}