// FUNC_NAME: InputDeviceManager::applyControllerRumble
void __thiscall InputDeviceManager::applyControllerRumble(
    int this, 
    bool bEnableEffect,          // param_1: non-zero to attempt effect
    float fIntensitySecondary,   // param_2: intensity for secondary motor (cast to float)
    bool bIsPrimaryMotor,        // param_3: false = primary? selects between left/right?
    uint8_t uiIntensityPrimary   // param_4: intensity for primary motor (0-255)
)
{
    int iRumbleDataValid;
    int iVTable;
    undefined4 uTime;
    float fFloatCast;
    undefined4 aLocal20[4]; // unused in effect path? Used in reset path.

    // Attempt to apply rumble effect if conditions met
    if (bEnableEffect &&
        (*(int *)(DAT_012234c4 + 0x24) != 0) &&
        (iVTable = (**(code **)(**(int **)(DAT_012234c4 + 0x24) + 4))(this + 0x30), iVTable != 0) &&
        (DAT_0121b0ac != 0))
    {
        int iRumbleConfig;
        if (bIsPrimaryMotor)
            iRumbleConfig = DAT_0121b638;
        else
            iRumbleConfig = DAT_0121b63c;

        if (iRumbleConfig != 0)
        {
            uTime = FUN_00414aa0();          // Get current time or timestamp
            fFloatCast = (float)uiIntensityPrimary;
            FUN_0060add0(DAT_0121a394, *(undefined4 *)(DAT_0121b0ac + 0x18), uTime);
                                              // Set primary motor effect
            uTime = FUN_00414aa0();
            fFloatCast = fIntensitySecondary;
            FUN_0060add0(DAT_0121a394, *(undefined4 *)(DAT_0121b0ac + 0x1c), uTime);
                                              // Set secondary motor effect

            undefined4 uMotorParam;
            if (bIsPrimaryMotor)
                uMotorParam = *(undefined4 *)(DAT_0121b638 + 0x20);
            else
                uMotorParam = *(undefined4 *)(DAT_0121b63c + 0x24);
            FUN_0060add0(DAT_0121a390, uMotorParam, iVTable);

            if (bIsPrimaryMotor)
                uMotorParam = *(undefined4 *)(DAT_0121b638 + 0x24);
            else
                uMotorParam = *(undefined4 *)(DAT_0121b63c + 0x28);
            FUN_0060add0(DAT_0121a390, uMotorParam, *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x24) + 0x70);

            FUN_00537af0();                  // Finalize rumble update
            return;
        }
    }

    // Fallback: reset rumble to zero
    if (*(int *)(DAT_0121b0ac + 0x18) != 0)
    {
        aLocal20[0] = 0;
        aLocal20[1] = 0;
        aLocal20[2] = 0;
        fFloatCast = (float)uiIntensityPrimary;
        FUN_0060add0(DAT_0121a394, *(int *)(DAT_0121b0ac + 0x18), aLocal20);
    }

    int iMotorConfig = 0;
    if (bIsPrimaryMotor)
    {
        if (DAT_0121b638 == 0)
            return;
        iMotorConfig = *(int *)(DAT_0121b638 + 0x20);
    }
    else
    {
        if (DAT_0121b63c == 0)
            return;
        iMotorConfig = *(int *)(DAT_0121b63c + 0x24);
    }

    if (iMotorConfig != 0)
    {
        aLocal20[0] = 0;
        aLocal20[1] = 0;
        aLocal20[2] = 0;
        fFloatCast = 0.0f;
        FUN_0060add0(DAT_0121a390, iMotorConfig, aLocal20);
    }
    return;
}