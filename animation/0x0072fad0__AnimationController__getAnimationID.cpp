// FUNC_NAME: AnimationController::getAnimationID
uint __fastcall AnimationController::getAnimationID(int *thisPtr)
{
    byte virtualResult;
    uint i, counterIndex;
    float *floatArray;
    int playerObj;
    byte flags;

    // Default return value (some sentinel)
    uint result = 0x2ca3cff6;

    if ((thisPtr != NULL) &&
        (playerObj = FUN_0043b870(DAT_01131040), playerObj != NULL) &&
        (*(int *)(playerObj + 0x1c) != 0) &&
        (*(int *)(playerObj + 0x1c) != 0x48))   // +0x1c seems to be current vehicle or special state
    {
        // Call virtual function at vtable offset 0x270 (index 0x9C)
        virtualResult = (*(code **)(*(int *)thisPtr + 0x270))();

        switch (virtualResult)
        {
            case 1:
                return 0xdd7d2351; // walk?
            case 2:
                return 0x8ed3e590; // run?
            case 3:
            case 4:
                return 0x94c92c21; // sprint?
        }

        // Get a rotating index from global counters
        counterIndex = DAT_010c2678 & DAT_012054b4;
        DAT_012054b4 = DAT_012054b4 + 1;

        floatArray = &DAT_010c2680; // array of floats, indexed by counterIndex
        if (floatArray[counterIndex] <= DAT_00d62b4c)
        {
            result = 0x35e0b005; // idle?
        }
        else
        {
            flags = *(byte *)(playerObj + 0x44); // movement flags at +0x44
            if (flags & 0x04)
                return 0x4ec7ced6;
            if (flags & 0x08)
                return 0xc609c0ce;
            if (flags & 0x10)
                return 0x6aeca40;
            if (flags & 0x20)
                return 0xd062398b;
            if (flags & 0x40)
                return 0x90dcb113;
            if (flags & 0x80)
                return 0x8c5068a9;
        }
    }
    return result;
}