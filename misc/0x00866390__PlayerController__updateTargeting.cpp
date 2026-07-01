// FUNC_NAME: PlayerController::updateTargeting
void __thiscall PlayerController::updateTargeting(int *this, float deltaTime, int *outTargetHandle, float *outTargetAngle, char *outHasTarget, float *outSensitivity)
{
    float fVar1;
    char cStrChar;
    char cTemp;
    char *pcString;
    int iVarSim1;
    int iVarSim2;
    int iVarSim3;
    float10 fVarTemp;
    float closestDist;
    undefined1 local_1c[4];
    undefined8 uStack_18; // 8 bytes
    float fStack_10; // +0x8 relative to uStack_18
    undefined1 local_c[12]; // buffer for ID

    // Accumulate timer at offset +0x3c8 * 4 = 0xF20
    fVar1 = (float)this[0x3c8]; // +0xF20: elapsedTime
    this[0x3c8] = (int)(deltaTime + fVar1);

    // Check bit at offset +0xf2a (byte offset 0xf2a) and compare with global kickOutTime
    if (((*(byte *)((int)this + 0xf2a) & 1) == 0) && (DAT_00d5c458 <= deltaTime + fVar1))
    {
        FUN_008623a0(); // startCooldown?
    }

    // Determine which distance pair to use based on a string lookup from deltaTime
    pcString = (char *)FUN_00549a40(&deltaTime); // likely hash or compare deltaTime to something
    cStrChar = *pcString;
    if (cStrChar == '\0')
    {
        deltaTime = (float)this[0x467] - (float)this[1000]; // +0x119C and +0xFA0
    }
    else
    {
        deltaTime = (float)this[0x468] - (float)this[0x3e9]; // +0x11A0 and +0xFA4
    }
    // Clamp to minimum distance
    if (deltaTime < DAT_00d5eee4)
    {
        deltaTime = DAT_00d5eee4;
    }

    // Get singleton manager
    iVarSim1 = FUN_00471610(); // getSimManager()
    cTemp = FUN_00865000(iVarSim1 + 0x30, local_c, &closestDist, local_1c); // getClosestTarget?
    fVar1 = DAT_00d5ccf8; // defaultFOV
    if (cTemp != '\0')
    {
        fVar1 = closestDist;
    }
    closestDist = fVar1;

    // Virtual call at vtable+0x1b0 (probably getTime or getInput)
    fVarTemp = (float10)(**(code **)(*this + 0x1b0))();
    if ((float10)DAT_00d75700 <= fVarTemp)
    {
        // Virtual call at vtable+0x4c (probably getPosition)
        (**(code **)(*this + 0x4c))(&uStack_18);
    }
    else
    {
        // Use stored vector from singleton
        iVarSim1 = FUN_00471610();
        uStack_18 = *(undefined8 *)(iVarSim1 + 0x20); // x,y as double? Assuming two floats
        fStack_10 = *(float *)(iVarSim1 + 0x28); // z
        if (cStrChar != '\0')
        {
            uStack_18._4_4_ = (float)((ulonglong)uStack_18 >> 0x20);
            uStack_18 = CONCAT44(uStack_18._4_4_ * DAT_00d5ccf8, (float)uStack_18 * DAT_00d5ccf8);
            fStack_10 = fStack_10 * DAT_00d5ccf8;
        }
    }

    // Get three different manager vectors
    iVarSim1 = FUN_00471610();
    iVarSim2 = FUN_00471610();
    iVarSim3 = FUN_00471610();
    // Compute dot product of object's direction with target direction
    if (_DAT_00d75c98 <
        (float)this[0x3fc] * *(float *)(iVarSim2 + 0x24) + // +0x3fc*4=0xFF0: directionX
        (float)this[0x3fb] * *(float *)(iVarSim1 + 0x20) + // +0x3fb*4=0xFEC: directionY? Adjust indices: 0x3fb-0x3f8? Actually: 0x3fb,0x3fc,0x3fd likely consecutive x,y,z
        (float)this[0x3fd] * *(float *)(iVarSim3 + 0x28))  // +0x3fd*4=0xFF4: directionZ
    {
        // Within lock-on threshold
        *outTargetHandle = 0;
        *outTargetAngle = _DAT_00d5780c; // defaultAngle
        *outHasTarget = 1;
        fVarTemp = (float10)(**(code **)(*this + 0x1b0))();
        if (fVarTemp < (float10)DAT_00d75700)
        {
            FUN_00866240(); // endLockOn?
            return;
        }
    }
    else
    {
        iVarSim1 = FUN_00471610();
        fVarTemp = (float10)FUN_004a0b00(iVarSim1 + 0x30, &uStack_18, local_c, &DAT_00d75690); // angleDot?
        // Check if within angle or distance
        if (((float10)_DAT_00d75c90 <= fVarTemp) || (closestDist <= deltaTime * DAT_00e4475c))
        {
            // No lock-on
            *outTargetHandle = DAT_00d5f520; // some handle constant
            *outTargetAngle = 0.0f;
            *outHasTarget = 0;
        }
        else
        {
            FUN_0085fa40(outTargetHandle, outTargetAngle, outHasTarget, deltaTime - closestDist, 0x3f800000); // 1.0f
            fVarTemp = (float10)(**(code **)(*this + 0x1b0))();
            if (fVarTemp < (float10)DAT_00d75700)
            {
                cStrChar = FUN_0085e970(); // sendEvent?
                FUN_00549ac0(cStrChar == '\0'); // setFlag?
            }
        }
        // Check string comparison on outTargetHandle to set sensitivity
        pcString = (char *)FUN_00549a40(&outTargetHandle);
        if (*pcString != '\0')
        {
            *outSensitivity = _DAT_00d5780c;
            return;
        }
        *outSensitivity = DAT_00d5ccf8;
    }
    return;
}