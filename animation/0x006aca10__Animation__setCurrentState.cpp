// FUNC_NAME: Animation::setCurrentState

// 0x006aca10 - Sets the current animation state index and updates flags/timers
void __thiscall Animation::setCurrentState(int thisPtr, uint* newStateIndex)
{
    uint oldIndex;
    float fVar1;
    int elementIndex;
    
    oldIndex = *(uint*)(thisPtr + 0x3d0); // currentStateIndex
    if (*newStateIndex != oldIndex) {
        // If there was a previous state and it's not a "transition" state (1)
        if ((oldIndex < 20) && 
            (elementIndex = oldIndex * 0x30 + thisPtr, *(int*)(elementIndex + 0x34) != 1)) {
            // Reset sub-timer in the old state element (offset +0x20 within element)
            *(int*)(elementIndex + 0x20) = 0;
        }
        oldIndex = *newStateIndex;
        *(uint*)(thisPtr + 0x3d0) = oldIndex; // Update current state index

        elementIndex = *(int*)(oldIndex * 0x30 + 0x34 + thisPtr); // State type of new element
        if (elementIndex == 0) {
            // State type 0: entry state
            *(uint*)(thisPtr + 0x3d4) |= 1; // Set flag 0x1
            (*(int*)(thisPtr + 0x3dc))++;   // Increment state counter
            fVar1 = (float)*(int*)(thisPtr + 0x3dc); // Counter as float
            if (*(int*)(thisPtr + 0x3dc) < 0) {
                fVar1 += 0.0f; // No-op for negative? DAT_00e44578 likely 0
            }
            // Random probability roll
            uint tempPtr = 0;
            FUN_008934e0(0xc22b9e2a, &tempPtr); // Get random value (float?)
            if ((float)tempPtr < fVar1) {
                FUN_00894ea0(0xc22b9e2a, fVar1, 0); // Set random state?
            }
        }
        else if (elementIndex == 3) {
            // State type 3
            *(uint*)(thisPtr + 0x3d4) |= 1;
        }
        else if (elementIndex == 1) {
            // State type 1 (transition)
            *(uint*)(thisPtr + 0x3d4) |= 2;
        }
        else if (elementIndex == 2) {
            // State type 2
            *(uint*)(thisPtr + 0x3d4) |= 4;
        }
        FUN_006abf80(); // Post-state-change update callback
    }
    return;
}