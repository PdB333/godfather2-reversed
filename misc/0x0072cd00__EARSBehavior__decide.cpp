// FUNC_NAME: EARSBehavior::decide

void __thiscall EARSBehavior::decide(int *thisObj, int param1, int param2, int param3)
{
    int result;
    float threshold;
    float value1;
    float value2;

    // Check bit 2 of state flags at offset +0x1F5C (0x7D7 * 4)
    if ((((uint)thisObj[0x7D7] >> 2) & 1) == 0)
    {
        // First call: set the flag and call init with param1
        thisObj[0x7D7] |= 4;  // Set bit 2
        result = 0;
        int initVal = FUN_006fbc40(0, 0);
        FUN_007f96a0(param1, 0, initVal, result);
    }
    else
    {
        // Subsequent calls: compare two virtual functions
        value1 = (float)(**(code **)(*thisObj + 0xC0))();  // Virtual method at +0xC0
        value2 = (float)(**(code **)(*thisObj + 0xC4))();  // Virtual method at +0xC4
        threshold = (float)(float)_DAT_00d62b30;  // Global threshold value
        result = 0;
        if (value2 * threshold <= value1)
        {
            // Use param3 (the fourth argument)
            int initVal = FUN_006fbc40(0, 0);
            param1 = param3;  // Overwrite param1 with param3
            FUN_007f96a0(param1, 0, initVal, result);
        }
        else
        {
            // Use param2 (the third argument)
            int initVal = FUN_006fbc40(0, 0);
            param1 = param2;  // Overwrite param1 with param2
            FUN_007f96a0(param1, 0, initVal, result);
        }
    }
    FUN_006fbc70();  // Cleanup / finalize
    return;
}