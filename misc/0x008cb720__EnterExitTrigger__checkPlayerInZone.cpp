// FUNC_NAME: EnterExitTrigger::checkPlayerInZone
void __thiscall EnterExitTrigger::checkPlayerInZone(int thisPtr, int *triggerId)
{
    int playerStatePtr;
    float playerDeltaX, playerDeltaY, playerDeltaZ, playerMovementSq;
    float thresholdSq;
    float radius;

    FUN_008cc410(triggerId); // Likely validate trigger ID

    if (DAT_012069d4 == *triggerId) // Check if this trigger's ID matches the active one
    {
        if (**(int **)(DAT_012233a0 + 4) == 0) // If no player manager
        {
            playerStatePtr = 0;
        }
        else
        {
            playerStatePtr = **(int **)(DAT_012233a0 + 4) + -0x1f30; // Offset to player state
        }

        playerMovementSq = DAT_00d5f6f0; // Default movement squared (perhaps a large value)

        if ((playerStatePtr != 0) && (*(int *)(thisPtr + 0x4c) != 0)) // If player exists and some flag is set
        {
            // Get player's previous position
            playerStatePtr = FUN_00471610();
            float prevX = *(float *)(playerStatePtr + 0x30);
            float prevY = *(float *)(playerStatePtr + 0x34);
            float prevZ = *(float *)(playerStatePtr + 0x38);

            // Get player's current position
            playerStatePtr = FUN_00471610();
            float currX = *(float *)(playerStatePtr + 0x30);
            float currY = *(float *)(playerStatePtr + 0x34);
            float currZ = *(float *)(playerStatePtr + 0x38);

            // Compute squared movement delta
            playerDeltaX = currX - prevX;
            playerDeltaY = currY - prevY;
            playerDeltaZ = currZ - prevZ;
            playerMovementSq = playerDeltaX * playerDeltaX + playerDeltaZ * playerDeltaZ + playerDeltaY * playerDeltaY;
        }

        // Check if not inside yet (flag at +0x50 bit 0 is 0) -> entry threshold
        if ((*(unsigned char *)(thisPtr + 0x50) & 1) == 0)
        {
            radius = *(float *)(thisPtr + 0x48) * DAT_00d7c2d0; // Radius * entry multiplier
            thresholdSq = radius * radius;
            if (playerMovementSq < thresholdSq)
            {
                // Move pointer to sub-state (offset +0x44, or 0 if thisPtr is 0xc sentinel)
                int subTriggerPtr = (thisPtr == 0xc) ? 0 : (thisPtr + 0x44);
                FUN_008cb440(subTriggerPtr, playerMovementSq); // Handle entry transition
            }
        }
        else // Already inside, check for exit (higher threshold)
        {
            if (((*(unsigned char *)(thisPtr + 0x24) & 1) == 0) && // Some other flag not set
                (radius = *(float *)(thisPtr + 0x48) * _DAT_00d7c2d4, // Exit multiplier (larger)
                 radius * radius < playerMovementSq))
            {
                int subTriggerPtr = (thisPtr == 0xc) ? 0 : (thisPtr + 0x44);
                FUN_008cb480(subTriggerPtr, playerMovementSq); // Handle exit transition
                return;
            }
        }
    }
    return;
}