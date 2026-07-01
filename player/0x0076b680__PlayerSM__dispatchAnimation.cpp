// FUNC_NAME: PlayerSM::dispatchAnimation
void __thiscall PlayerSM::dispatchAnimation(int* thisPtr, int animDefault, int animIdle, int animActive, int animSpecial, int animOther)
{
    // Offsets:
    // +0x5C  -> controller pointer (int*)
    // +0x70  -> current overlay/animation slot (used as pointer - 0x48)
    // +0x74C -> state data pointer inside controller
    // +0x160 -> state data flag (byte)
    // +0x8E0 -> controller flags (bit 10 tested)
    // +0x1B8C -> overlay state (byte 0,1,4)

    int currentOverlay = thisPtr[0x1C];
    if (currentOverlay == 0 || currentOverlay == 0x48)
        return;

    int* controller = (int*)thisPtr[0x17];

    int* stateData = *(int**)((char*)controller + 0x74C);
    bool altPath = false;
    if (stateData != 0 && (int)stateData != 0x48 &&
        *(char*)((char*)stateData + 0x160) == 2 &&
        (*(unsigned int*)((char*)controller + 0x8E0) >> 10 & 1) != 0)
    {
        altPath = true;
    }

    // Derive overlay base pointer (size of one overlay = 0x48 bytes)
    int* overlayBase = (currentOverlay == 0) ? 0 : (int*)((char*)currentOverlay - 0x48);
    char overlayState = (overlayBase != 0) ? *(char*)((char*)overlayBase + 0x1B8C) : 0;

    // Virtual function at vtable[0x2C]: playAnimation(int handle, int mode, int unk, float blendIn, float blendOut)
    auto playAnim = (void (__fastcall*)(int*, int, int, int, float, float))(*(int**)thisPtr)[0x2C / 4];

    if (altPath)
    {
        if (overlayState == 0)
        {
            playAnim(thisPtr, animSpecial, 1, 0, 1.0f, 1.0f);
        }
        else if (overlayState == 1)
        {
            playAnim(thisPtr, animOther, 1, 0, 1.0f, 1.0f);
        }
        else if (overlayState == 4)
        {
            playAnim(thisPtr, animActive, 1, 0, 1.0f, 1.0f);
        }
        else
        {
            // default: use animDefault (passed as param_2)
            playAnim(thisPtr, animDefault, 1, 0, 1.0f, 1.0f);
        }
    }
    else
    {
        if (overlayState == 0)
        {
            playAnim(thisPtr, animDefault, 1, 0, 1.0f, 1.0f);
        }
        else if (overlayState == 1)
        {
            playAnim(thisPtr, animIdle, 1, 0, 1.0f, 1.0f);
        }
        else if (overlayState == 4)
        {
            playAnim(thisPtr, animSpecial, 1, 0, 1.0f, 1.0f);
        }
        else
        {
            // default fallback: use animActive
            playAnim(thisPtr, animActive, 1, 0, 1.0f, 1.0f);
        }
    }
}