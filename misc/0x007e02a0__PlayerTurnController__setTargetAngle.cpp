// FUNC_NAME: PlayerTurnController::setTargetAngle

// Function at 0x007e02a0: Handles setting a new target angle for the player's turn.
// Compares new angle with stored angle (at +0x78), processes transitions via timers and flags.

bool __thiscall PlayerTurnController::setTargetAngle(int thisObj, int newAngleDeg)
{
    bool result = false; // local_5

    // If the new angle is the same as the currently stored angle, no action needed.
    if (*(int*)(thisObj + 0x78) != newAngleDeg) {
        // Early exit: if game is paused and input is NOT blocked, allow the change.
        if (isGamePaused()) {
            if (!isInputBlocked(0)) {
                return true;
            }
        }

        // Access a component at this+0x58, then offset 0x74c to get a base pointer,
        // presumably a state machine component. Subtract 0x48 to get its parent structure.
        int componentBase = *(int*)(*(int*)(thisObj + 0x58) + 0x74c);
        if (componentBase == 0) {
            componentBase = 0;
        } else {
            componentBase = componentBase - 0x48;
        }

        // The byte at +0x1A8 must be 1 for this transition to proceed (likely "canTurn" flag).
        if (*(char*)(componentBase + 0x1A8) == 1) {
            // Re-check if game is paused, now leads to immediate reject.
            if (isGamePaused()) {
                return false;
            }

            bool isInCombat = isCombatMode(); // FUN_00701010
            void* timerObj = allocateMemory(0x38); // FUN_00798f50(0x38)
            bool timerCreated; // cVar2
            if (!isInCombat) {
                timerCreated = createNormalTimer(timerObj); // FUN_0079e970
            } else {
                timerCreated = createCombatTimer(timerObj); // FUN_0079e920
            }

            float currentTime = getGameTime(); // FUN_00701020
            bool angleTimeout = checkAngleTimeout(newAngleDeg, currentTime); // FUN_007dfed0

            if (!timerCreated) {
                // Non-combat branch
                if (!angleTimeout) {
                    return false;
                }
                if (*(char*)(thisObj + 0x7D) == 0) {
                    return false;
                }
                *(char*)(thisObj + 0x7D) = 0; // Clear turn-in-progress flag
            } else {
                // Combat branch
                if (!angleTimeout) {
                    if (*(char*)(thisObj + 0x7D) != 0) {
                        return false; // Already turning, reject
                    }
                    // Check if we are still in combat (may have changed)
                    if (isCombatMode()) {
                        return false;
                    }
                    int lastAngle = getLastTurnAngle(); // FUN_007ab290
                    int angleDiff = newAngleDeg - lastAngle;
                    float fAngleDiff = (float)angleDiff;
                    if (angleDiff < 0) {
                        fAngleDiff = fAngleDiff + 360.0f; // Wrap around for degrees
                    }
                    // Compare scaled angle difference with a threshold based on current time
                    float scaledAngle = fAngleDiff * ANGLE_SCALE_FACTOR; // DAT_00d5efb8
                    float timeThreshold = TIME_THRESHOLD_FACTOR * currentTime; // _DAT_00e533d0
                    if (scaledAngle < timeThreshold) {
                        return false; // Too small an angle to turn
                    }
                    *(char*)(thisObj + 0x7D) = 1; // Mark turn-in-progress
                    return false; // Action queued, but not yet executed
                }
            }
            result = true;
        }
    }
    return result;
}