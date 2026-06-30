// FUN_00470550: AnimationController::setPlaybackSpeed
void __thiscall AnimationController::setPlaybackSpeed(int* pThis, int speedParam)
{
    // Clear loop mode flags (bits 2-3) at offset +0x15e
    *(ushort*)((int)pThis + 0x15e) &= 0xfff3;

    // If animation is currently playing (bit 4 of flags set), stop it and clear bit 4
    if ((*(byte*)((int)pThis + 0x15e) >> 4 & 1) != 0)
    {
        *(ushort*)((int)pThis + 0x15e) &= 0xffef; // clear bit 4
        // Call virtual function at vtable+0x70 (likely stopAnimation)
        (*(void (__thiscall **)(void*))(*(int*)pThis + 0x70))(pThis);
    }

    if (speedParam != 0)
    {
        float fVal = (float)speedParam;
        if (speedParam < 0)
        {
            // Compensate for negative int conversion (add 2^32 as float)
            fVal = fVal + DAT_00e44578;
        }
        // Store inverse of playback speed at offset +0x154 (pThis[0x55])
        pThis[0x55] = (int)(1.0f / fVal);
        return;
    }

    // speedParam == 0: reset to default speed stored at +0x150
    float defaultSpeed = *(float*)(pThis + 0x54); // offset +0x150
    if (defaultSpeed != DAT_00e2b1a4) // global constant (likely 0.0f or 1.0f)
    {
        *(float*)(pThis + 0x54) = DAT_00e2b1a4;
        *(ushort*)((int)pThis + 0x15e) |= 0x100; // set flag bit 8 (dirty)
    }
    // Call internal update function (FUN_004705e0)
    AnimationController::updateInternalState();
}