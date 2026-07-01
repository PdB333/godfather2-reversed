// FUNC_NAME: Player::updateGameplayAndAiming
void __fastcall Player::updateGameplayAndAiming(int thisPtr)
{
    int hashLookupResult;
    int globalObj;
    bool bFlag;
    float someFloat;
    char inputActive;
    int someIndex;
    uint flags;
    int* vtablePtr;
    byte byteFlag;
    int angleSourceObj;
    bool bTemp;
    float10 angleCalc;
    undefined4 aimingInputX;
    undefined4 aimingInputY;
    undefined4 aimingInputZ;
    undefined4 stackVar;
    float angleOffset;

    // Check if some state index is valid (not 0 and not 72)
    if ((*(int *)(thisPtr + 0xb0) != 0) && (*(int *)(thisPtr + 0xb0) != 0x48)) {
        hashLookupResult = LookupObjectByHash(0xb47bb605, 0); // Lookup main character object
    }

    byteFlag = 0;
    if (hashLookupResult != 0) {
        // Clear bit 0 of flags at offset 0x1d0 if set
        if ((*(byte *)(hashLookupResult + 0x1d0) & 1) != 0) {
            *(uint *)(hashLookupResult + 0x1d0) = *(uint *)(hashLookupResult + 0x1d0) & 0xfffffffe;
        }
        byteFlag = (byte)(*(uint *)(hashLookupResult + 0x1d0) >> 4) & 1; // Check bit 4
    }

    // Set some flag in the player manager object
    *(undefined1 *)(*(int *)(thisPtr + 0xa0) + 0xa20) = 1;

    // Check if certain flag is set for menu overlay
    if ((((*(byte *)(*(int *)(thisPtr + 0xa0) + 0x8e6) & 1) != 0) &&
        (*(undefined4 *)(*(int *)(thisPtr + 0xa0) + 0x1eb4) = DAT_01205224,
        *(int *)(thisPtr + 0xa0) != 0)) && (globalObj = GetGlobalObject(DAT_0112a9fc), globalObj != 0)) {
        // Handle menu display update
        UpdateMenuDisplay();
    }

    // Allocate some render state (size 0x30)
    PushRenderState(0x30);

    // Call a virtual function on the player manager object: index 0x290 (offset 0x290 in vtable? or function pointer at +0x290)
    // Possibly update some camera or control mode
    (**(code **)(**(int **)(thisPtr + 0xa0) + 0x290))(1, 8);

    // Check if bit 4 in our flags is set
    if ((*(uint *)(thisPtr + 0x9c) >> 4 & 1) != 0) {
        // Set some render state to fog color
        SetRenderState(0, 0, DAT_00d5ef90);
        *(uint *)(thisPtr + 0x9c) = *(uint *)(thisPtr + 0x9c) & 0xffffffef; // Clear bit 4
    }

    // Set flag in player manager
    *(undefined1 *)(*(int *)(thisPtr + 0xa0) + 0xa20) = 1;

    // Set a global flag (DAT_011298f8+0x10) bit 1
    *(uint *)(DAT_011298f8 + 0x10) = *(uint *)(DAT_011298f8 + 0x10) | 2;

    bFlag = true;
    if (*(int *)(thisPtr + 0x74) == 0) goto LAB_007736a7;

    flags = *(uint *)(*(int *)(thisPtr + 0x74) + 0x24); // Flags from input controller?
    if (byteFlag == 0) {
        // Check if both bits 12 and 13 (0x3000) are set
        flags = flags & 0x3000;
        if (flags != 0x3000) {
            bTemp = (flags == 0x2000);
            goto LAB_007736a3;
        }
    } else {
        // Check bits 9 and 10 (0x600)
        flags = flags & 0x600;
        if (flags != 0x600) {
            bTemp = (flags == 0x400);
            LAB_007736a3:
            if (!bTemp) goto LAB_007736a7;
        }
    }
    bFlag = false; // Some condition met, so we want to allow something

LAB_007736a7:
    // If bit 3 in flags is set and bFlag is true, call virtual function at offset 0x27c
    if (((*(uint *)(thisPtr + 0x9c) >> 3 & 1) != 0) && (bFlag)) {
        (**(code **)(**(int **)(thisPtr + 0xa0) + 0x27c))();
    }

    someIndex = *(int *)(*(int *)(thisPtr + 0xa0) + 0x2124); // Get some index from player manager
    inputActive = IsInputActive();
    if ((inputActive != '\0') && (someIndex != 0)) {
        SetInputMode(1); // Enable game input mode
    }

    UpdateAudio();
    UpdateParticleEffects(thisPtr);

    // Main aiming logic block
    if (((((hashLookupResult != 0) && ((*(uint *)(hashLookupResult + 0x1d0) >> 0xb & 1) != 0)) &&
         (*(uint *)(hashLookupResult + 0x1d0) = *(uint *)(hashLookupResult + 0x1d0) & 0xfffff7ff, // Clear bit 11
         *(int *)(thisPtr + 0xa0) != 0)) &&
        ((hashLookupResult = GetGlobalObject(DAT_0112afb8), hashLookupResult != 0 &&
         (angleSourceObj = *(int *)(hashLookupResult + 0x1c), angleSourceObj != 0)))) &&
       ((angleSourceObj != 0x3c && (inputActive = IsPlayerAlive(), someFloat = DAT_00d5e288, inputActive == '\0')))) {

        // Read aiming input (two values from stack)
        stackVar = 0;
        ReadAimingInput(&stackVar, &angleOffset); // Gets X, Y offsets? Actually stack layout
        int aimAxisIndex = *(int *)(*(int *)(thisPtr + 0xa0) + 0x1f48); // 0,1,2 for axis selection
        aimingInputX = 0;
        if (aimAxisIndex == 0) {
            aimingInputX = *(undefined4 *)(angleSourceObj + 0xe4);
        } else if (aimAxisIndex == 1) {
            aimingInputX = *(undefined4 *)(angleSourceObj + 0xe0);
        } else if (aimAxisIndex == 2) {
            aimingInputX = *(undefined4 *)(angleSourceObj + 0xe8);
        }
        // Calculate angle offset from player position
        angleOffset = (someFloat - _DAT_00d5780c) - *(float *)(hashLookupResult + 0x40);
        StartAimCalculation(8);
        aimingInputY = 0;
        aimingInputZ = 1;
        angleCalc = (float10)CalculateAngle(aimingInputX, angleOffset, 1, 0);
        ApplyAimAngle((float)angleCalc, aimingInputZ, aimingInputY);

        // Additional condition for firing/action
        if (((someIndex != 0) && (inputActive = CanUseAbility(), inputActive == '\0')) &&
           ((inputActive = IsInMenu(*(undefined4 *)(thisPtr + 0xa0), 2), inputActive == '\0' &&
            (inputActive = IsPlayerAlive(), inputActive != '\0')))) {
            // Get a global game object
            int gameObj;
            if (**(int **)(DAT_012233a0 + 4) == 0) {
                gameObj = 0;
            } else {
                gameObj = **(int **)(DAT_012233a0 + 4) + -0x1f30;
            }
            int* vtable = (int *)GetGameObjectByIndex(gameObj);
            // Call virtual function at offset 0x28 (likely "TriggerAbility" or similar)
            (**(code **)(*vtable + 0x28))(0x83f631c5, 0, 0xffffffff, 0);
            // Log event
            int logParam = 0;
            logParam = GetLoggingContext(0, 0);
            LogGameEvent(0xf006f9c7, 0x4c, logParam, aimingInputZ);
            EndLoggingContext();
        }
    }
    return;
}