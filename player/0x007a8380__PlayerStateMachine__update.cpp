// FUNC_NAME: PlayerStateMachine::update
// Address: 0x007a8380
// Likely a per-frame update for a player state machine. Handles resource cleanup, state-specific updates, and UI checks.

void __fastcall PlayerStateMachine::update(int thisPtr)
{
    bool isPaused;
    int stateBase;
    int *resourcePtr;

    // Possibly update input or game state
    updateInput();

    isPaused = isGamePaused();
    if (isPaused) {
        displayPauseOverlay(); // Maybe show HUD or pause menu
    }

    // Check if we have a state instance at +0x74c (pointer to current state object +0x48 offset)
    int stateObjPlus48 = *(int *)(thisPtr + 0x74c); // +0x74c: pointer to state + 0x48
    if ((stateObjPlus48 != 0) && (stateObjPlus48 != 0x48)) {
        // Get base of state object by subtracting 0x48 offset
        if (stateObjPlus48 == 0) {
            stateBase = 0;
        } else {
            stateBase = stateObjPlus48 - 0x48;
        }
        // Check state-specific data at +0x214 (maybe a sub-state or flag)
        int subStatePtr = *(int *)(stateBase + 0x214);
        if (subStatePtr == 0) {
            return;
        }
        if (subStatePtr == 0x48) {
            return;
        }

        // Get base again (redundant)
        if (stateObjPlus48 == 0) {
            stateBase = 0;
        } else {
            stateBase = stateObjPlus48 - 0x48;
        }

        // Check a bit flag at +0x1D0 (bit 4)
        if ((*(unsigned int *)(stateBase + 0x1D0) >> 4 & 1) == 0) {
            // Path without flag set – handle resource at +0x24AC
            resourcePtr = (int *)(thisPtr + 0x24AC);
            if ((*(int *)(thisPtr + 0x24AC) != 0) && (*(int *)(thisPtr + 0x24AC) != 0x48)) {
                // Get base of resource object (similar offset convention)
                int resourceBase;
                if (*resourcePtr == 0) {
                    resourceBase = 0;
                } else {
                    resourceBase = *resourcePtr - 0x48;
                }
                releaseResource(resourceBase);
                // Free the resource pointer
                deleteObject(resourcePtr);
                *resourcePtr = 0;
            }

            // Update main state machine logic
            updateStateMachine();

            // Call virtual functions on the state object
            int *stateVtable;
            if (stateObjPlus48 == 0) {
                stateVtable = (int *)0x0;
            } else {
                stateVtable = (int *)(stateObjPlus48 - 0x48);
            }
            // Virtual function at offset 0x170 (e.g., SetTimer, PlayAnimation)
            (**(code **)(*stateVtable + 0x170))(0, 0x1FF, 1, 0x3F800000, 0);
            // Virtual function at offset 0x7C (e.g., update, writeOutput)
            (**(code **)(*stateVtable + 0x7C))();

            updateAnimation(); // Possibly update animations
        } else {
            // Path with flag set
            handleSpecialState();

            // Call only the vtable+0x7C on the state object
            int *stateVtable2;
            if (stateObjPlus48 == 0) {
                // This branch seems buggy in decompilation (iRam00000000 appears)
                (**(code **)(0 + 0x7C))(); // fallback – likely invalid
            } else {
                stateVtable2 = (int *)(*(int *)(stateObjPlus48 - 0x48));
                (**(code **)(*stateVtable2 + 0x7C))();
            }
        }
    }

    // Re-check pause state
    isPaused = isGamePaused();
    if (isPaused) {
        updatePauseMenu(); // Or UI overlay update
    }
}