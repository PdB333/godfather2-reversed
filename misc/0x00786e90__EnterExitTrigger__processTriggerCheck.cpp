// FUNC_NAME: EnterExitTrigger::processTriggerCheck
void __fastcall EnterExitTrigger::processTriggerCheck(int this)
{
    float targetZoneTime = *(float *)(*(int *)(this + 0x2c88) + 0x74); // +0x2c88: pointer to zone data, +0x74: time threshold
    // Global game time from DAT_00d577a0 (likely gGameTime)
    if (gGameTime <= targetZoneTime && *(int *)(this + 0x1a3c) != 0) // +0x1a3c: activator count
    {
        int gameManager;
        if (**(int **)(DAT_012233a0 + 4) == 0)
            gameManager = 0;
        else
            gameManager = **(int **)(DAT_012233a0 + 4) - 0x1f30; // offset to GodfatherGameManager

        int playerPtr = FUN_00471610(); // likely returns Player pointer or something
        if (*(int *)(gameManager + 0x1ed8) == 0) // +0x1ed8: current player pointer offset
            gameManager = 0;
        else
            gameManager = *(int *)(gameManager + 0x1ed8) - 0x48; // +0x48: offset to Player

        int dummy = 0;
        float distance = FUN_006b0900(playerPtr + 0x30, &dummy, gameManager, gameManager, 1); // compute distance from player to target

        if (distance >= 0.0f && distance < targetZoneTime)
        {
            *(uint *)(this + 0x2c6c) |= 0x40; // set flag: proximity triggered
            FUN_00785e30(0); // activate trigger event
            return;
        }
    }

    if ((*(uint *)(this + 0x2c6c) & 0x40) != 0) // if proximity flag was set
    {
        *(uint *)(this + 0x2c6c) &= ~0x40; // clear flag
        int* activatorArray = (int*)(this + 0x193c); // +0x193c: start of activator data array
        int count = *(int *)(this + 0x1a3c); // number of activators
        int* end = activatorArray + count; // each element 4 bytes
        for (int* it = activatorArray; it != end; ++it)
        {
            FUN_007880d0(); // reset activator state
        }

        if ((*(uint *)(this + 0x2c6c) & 0x4) == 0) // bit 2: timer A not set
        {
            FUN_0083c930(this + 0x10, 100); // set timer A to 100ms
            *(uint *)(this + 0x2c6c) |= 0x4;
        }
        if ((*(uint *)(this + 0x2c6c) & 0x8) == 0) // bit 3: timer B not set
        {
            FUN_0083c930(this + 0x10, 100); // set timer B to 100ms
            *(uint *)(this + 0x2c6c) |= 0x8;
        }
    }
}