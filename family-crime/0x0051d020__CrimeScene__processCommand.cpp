// FUNC_NAME: CrimeScene::processCommand

void CrimeScene::processCommand(void)
{
    int cmdType;          // *in_EAX
    int someID;           // in_EAX[1]
    int targetIndex;      // in_EAX[2]
    float *vectorPtr;     // in_EAX[3]
    float vecX, vecY, vecZ, vecW;
    int newState;
    int tmp;
    int objHandle;
    undefined4 local_1c, local_18, local_14;

    cmdType = *command;
    newState = 0;

    switch (cmdType)
    {
    case 1: // Start objective
    case 2: // Update objective
    case 3: // Complete objective? (these share same handler)
    case 4:
        someID = command[1];
        if (someID != 0)
        {
            // Assign objective ID to this->objectiveId (+0xb4)
            *(int *)(this + 0xb4) = someID;
            FUN_0044b210(someID); // Probably addRef on some resource

            vectorPtr = (float *)command[3];
            if ((vectorPtr != (float *)0x0) &&
                ((*vectorPtr != 0.0f || (vectorPtr[1] != 0.0f) || (vectorPtr[2] != 0.0f))))
            {
                vecX = vectorPtr[1]; // Note: order seems swapped? Actually vectorPtr[1] assigned to second float?
                vecY = vectorPtr[2];
                vecZ = vectorPtr[3];
                // Store the vector at offset +0xd0 (4 floats)
                *(float *)(this + 0xd0) = *vectorPtr;
                *(float *)(this + 0xd4) = vecX;
                *(float *)(this + 0xd8) = vecY;
                *(float *)(this + 0xdc) = vecZ;
                // Set pointer to the stored vector
                *(float **)(this + 0xbc) = (float *)(this + 0xd0);
            }

            // Check if game is running (FUN_004e92e0 returns non-zero if running)
            if (FUN_004e92e0() != 0)
            {
                if (command[2] < 1) // targetIndex <= 0 -> auto-select
                {
                    tmp = *(int *)(*(int *)(this + 0x10) + 0x2c); // Something from related object
                    if ((tmp == 0) || (FUN_004e92e0() == 0) || (tmp = FUN_004c3df0(tmp), tmp < 0))
                    {
                        newState = 1; // Failed to assign objective
                    }
                    else
                    {
                        *(int *)(this + 0xb8) = tmp; // Set target index
                        newState = 2; // Objective assigned
                    }
                }
                else
                {
                    *(int *)(this + 0xb8) = command[2]; // Use explicit target index
                    newState = cmdType; // Keep original command type? Actually newState = iVar6, which is cmdType (1-4)
                }
            }
            else
            {
                newState = 1; // Game not running -> fail
                *(int *)(this + 0xb8) = -1;
            }

            // Additional handling for case when a certain flag is set (0x40000000) in related object
            if ((*(uint *)(*(int *)(this + 0x10) + 0x14) & 0x40000000) != 0)
            {
                local_1c = 0;
                local_18 = 0;
                local_14 = 0;
                if (DAT_0116407c != (undefined4 *)0x0)
                {
                    local_14 = *DAT_0116407c;
                    local_1c = DAT_0116407c[1];
                }
                objHandle = FUN_00536ed0(*(int *)(this + 0xb8), &local_1c);
                if (objHandle != 0)
                {
                    newState = 4; // Special state (playback?)
                    *(int *)(this + 0xc0) = objHandle;
                }
            }
        }
        break;

    case 5: // Set objective (no state machine transitions?)
        *(int *)(this + 0xb4) = command[1];
        vectorPtr = (float *)command[3];
        newState = 5;
        if ((vectorPtr != (float *)0x0) &&
            ((*vectorPtr != 0.0f || (vectorPtr[1] != 0.0f) || (vectorPtr[2] != 0.0f))))
        {
            vecX = vectorPtr[1];
            vecY = vectorPtr[2];
            vecZ = vectorPtr[3];
            *(float *)(this + 0xd0) = *vectorPtr;
            *(float *)(this + 0xd4) = vecX;
            *(float *)(this + 0xd8) = vecY;
            *(float *)(this + 0xdc) = vecZ;
            *(float **)(this + 0xbc) = (float *)(this + 0xd0);
        }
        break;
    }

    // Cleanup: if previous state was 4 and we have a playback object, release it
    if ((*(int *)(this + 0xb0) == 4) && (*(int *)(this + 0xc0) != 0))
    {
        // Call vtable function to release object (likely via global vtable pointer)
        (**(code **)(*DAT_01194538 + 4))(*(int *)(this + 0xc0), 0);
        *(undefined4 *)(this + 0xc0) = 0;
    }

    // Update state and state function pointer
    *(int *)(this + 0xb0) = newState;
    *(code **)(this + 0x78) = stateFunctionTable[newState]; // PTR_LAB_00e38260
}