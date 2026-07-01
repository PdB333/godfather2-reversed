// FUNC_NAME: Player::processEnterExitInteraction
void __thiscall Player::processEnterExitInteraction(int thisPtr, int entityPtr, float timeDelta)
{
    bool isPaused;
    bool canInteract;
    int dummyOut;
    float globalTimeThreshold;
    char result;
    int switchResult[2]; // local_c
    char local_4;

    // Check if game is paused or globally blocked
    isPaused = FUN_007f47a0(); // likely IsGamePaused()
    if (!isPaused) {
        dummyOut = 0;
        // Check if interaction is possible (e.g., can enter vehicle/door)
        // param_2 (entityPtr) is reused as output pointer? Actually &param_2 -> address of entityPtr
        result = FUN_007e35f0(thisPtr + 0xac, entityPtr, &dummyOut);
        globalTimeThreshold = DAT_00d5f540; // some global timer threshold
        if (result == 0) {
            // Interaction not available? Check if character is in a special state (e.g., already inside)
            if (FUN_0071f4e0(*(undefined4 *)(thisPtr + 0x58))) {
                switchResult[0] = 0;
                switchResult[1] = 0;
                local_4 = 0;
                FUN_006e61a0(entityPtr); // call start or stop sound/anim
                local_4 = 1;
                FUN_007e3720(switchResult); // get result struct?
                if (switchResult[0] != 0) {
                    FUN_004daf90(switchResult); // free or process result
                }
            }
        } else {
            // Interaction available
            *(char *)(dummyOut + 8) = 1; // set flag on some output struct
            if ((timeDelta < globalTimeThreshold) && ((*(uint *)(*(int *)(entityPtr + 0x2124) + 0x20) >> 10 & 1U) == 0)) {
                FUN_0072fec0(0); // start some pre-interaction effect?
                // Set bit 0x400 (bit 10) on entity's state flags
                *(uint *)(*(int *)(entityPtr + 0x2124) + 0x20) |= 0x400;
                return;
            }
        }
    }
    return;
}