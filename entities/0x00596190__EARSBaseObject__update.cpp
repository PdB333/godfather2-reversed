// FUNC_NAME: EARSBaseObject::update
void __thiscall EARSBaseObject::update(EARSBaseObject *this, float inputValue)
{
    byte *pFlags = (byte *)((int *)this + 1); // +0x4? Actually offset +1 from base, so flags at this+1
    byte flags = *pFlags;
    bool setupDone = false;
    char tempBuffer1[44]; // e.g., time delta structure
    char tempBuffer2[4];
    char tempBuffer3[32];

    // Get system data (likely FrameInfo) from global singleton (DAT_012055a8)
    (*(void (__stdcall **)(char *))(*(DWORD *)DAT_012055a8 + 0x40))(tempBuffer1);

    if ((flags & 2) == 0) // bit 1 not set
    {
        float val = someMathFunc(inputValue); // FUN_00595490 - clamp/lerp?
        if ((flags & 1) != 0) // bit 0 set
        {
            val = someMathFunc(val);
            someMathFunc(val);
        }
        doSetupPhase(tempBuffer3); // FUN_0059bb50
        setupDone = true;
    }
    if ((flags & 4) == 0) // bit 2 not set
    {
        float val = someMathFunc(inputValue);
        if ((flags & 1) == 0) // bit 0 not set
        {
            doFinalPhase(tempBuffer2); // FUN_0059bde0
        }
        else
        {
            val = someMathFunc(val);
            someMathFunc(val);
            doFinalPhase(tempBuffer2);
        }
    }
    else if (!setupDone)
    {
        return;
    }
    // Virtual call at vtable offset 0x1c (index 7)
    (*(void (__thiscall **)(EARSBaseObject *))(*((int **)this) + 7))(this);
}