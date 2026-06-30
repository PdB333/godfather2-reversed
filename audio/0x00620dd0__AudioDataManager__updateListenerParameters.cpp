// FUNC_NAME: AudioDataManager::updateListenerParameters
void __thiscall AudioDataManager::updateListenerParameters(void)
{
    int thisPtr; // unaff_ESI, implicit this pointer
    float distance; // local_38
    int param1; // local_34
    int param2; // local_30
    int param3; // local_2c
    int param4; // local_28
    char localFlags; // local_24
    bool overrideFlag; // local_23
    int local_20; // saved global 1
    int local_1c; // saved global 2
    int local_18; // saved global 3
    int local_14; // field at +0x3C
    int local_10; // always 0
    int local_c; // always 0
    int local_8; // always 0

    // Read override flag from object (+0xC0). If false, use global override.
    overrideFlag = *(char *)(thisPtr + 0xC0);
    local_10 = 0;
    localFlags = 0;
    local_20 = DAT_00e2b1a4; // global constant, likely 0 or 1
    local_c = 0;
    local_8 = 0;
    if (overrideFlag == '\0') {
        overrideFlag = DAT_01205887; // global byte override, possibly debug flag
    }
    local_14 = *(int *)(thisPtr + 0x3C); // some object ID or parameter
    local_1c = DAT_00e2b04c; // global constant (float?)
    local_18 = DAT_00e2b050; // global constant (float?)
    param1 = DAT_00e2b1a4; // another global constant
    distance = 0.0f;
    param3 = DAT_00e2b1a4; // same constant
    param4 = 0;
    param2 = 0;

    // Compute distance and other parameters using a helper function.
    FUN_005e5270(&localFlags, &param4, &param1, &distance, &param3, &param2);

    // Enter audio system context (push state?)
    audioSystemBeginFrame();

    // Conditionally set an audio parameter based on distance.
    if (((*(int *)(thisPtr + 0xAC) != 0) &&
         (distance = distance * DAT_00e44748, distance <= DAT_00e2af34)) &&
        (DAT_00e2b05c <= distance))
    {
        audioSetParameter(0, distance); // set audio parameter index 0
    }

    // Always set another audio parameter.
    audioSetParameter(0, (float)param1);

    // Leave audio system context (pop state?)
    audioSystemEndFrame();

    return;
}