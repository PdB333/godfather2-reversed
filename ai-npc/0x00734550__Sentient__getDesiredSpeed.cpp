// FUNC_NAME: Sentient::getDesiredSpeed
float __thiscall Sentient::getDesiredSpeed(int someParam)
{
    float gameManagerSpeedMult;
    char localFlag;
    int gameManagerPtr;
    float currentSpeed;
    float directionalFactor;
    float ratio;

    // Check movement state at +0x2004
    int moveState = *(int*)((char*)this + 0x2004);
    if (moveState == 0 || moveState == 0x48)
    {
        // Return base speed at +0x1D78
        return (float)*(int*)((char*)this + 0x1D78);
    }

    // Access global game manager pointer (DAT_012233a0 + 4)
    gameManagerPtr = **(int**)(DAT_012233a0 + 4);
    if (gameManagerPtr == 0 || gameManagerPtr == 0x1F30)
    {
        return 0.0f;
    }

    // Read speed multiplier from game manager at +0x1FC
    gameManagerSpeedMult = *(float*)(gameManagerPtr + 0x1FC);

    // Call virtual functions for current speed and directional factor
    currentSpeed = (*(float(__thiscall**)(Sentient*))(*(int*)this + 0xC4))(this);
    directionalFactor = (*(float(__thiscall**)(Sentient*))(*(int*)this + 0xC0))(this);

    // Check timer at +0x824
    if ((float)*(int*)((char*)this + 0x824) <= gGlobalTimerThreshold) // DAT_01205228
    {
        // Check flag at +0x5F4
        if (*(int*)((char*)this + 0x5F4) != 0)
        {
            localFlag = FUN_009af6f0(someParam);
            if (localFlag == 0) goto RETURN_ZERO;
        }

        // Call virtual function at vtable+0x228
        localFlag = (*(char(__thiscall**)(Sentient*, int))(*(int*)this + 0x228))(this, someParam);
        if (localFlag == 0)
        {
            // Compute sub-object pointer based on moveState
            int subObjPtr;
            if (moveState == 0)
                subObjPtr = 0;
            else
                subObjPtr = moveState - 0x48; // -72 bytes

            float threshold1;
            float threshold2;
            if (subObjPtr != 0)
            {
                threshold1 = *(float*)(subObjPtr + 0xF4);
                threshold2 = *(float*)(subObjPtr + 0xF8);
            }
            else
            {
                threshold1 = 0.0f;
                threshold2 = 0.0f; // Actually undefined, but simplified
            }

            // Compare with ratio
            ratio = (float)((double)directionalFactor / (double)currentSpeed);
            float baseTerm = threshold1 * gameManagerSpeedMult + (gGlobalConstant - gameManagerSpeedMult); // _DAT_00d5780c
            if (baseTerm < ratio)
            {
                return FUN_007234c0();
            }

            baseTerm = threshold2 * gameManagerSpeedMult + (gGlobalConstant - gameManagerSpeedMult);
            if (baseTerm < ratio)
            {
                return FUN_007234c0();
            }

            return FUN_007234c0();
        }
    }

RETURN_ZERO:
    return 0.0f;
}