// FUNC_NAME: SimNpc::tickUpdate
void __fastcall SimNpc::tickUpdate(int *this)
{
    int iVar1;
    byte flagsByte;
    char bResult;
    int iVar4;
    float fTimer;
    byte localBuffer[12]; // Stack space for a temporary transform or state
    int pad1; // alignment?
    int pad2;
    int pad3;
    int pad4;

    flagsByte = *(byte *)((int)this + 0x39e); // State flags (bit6 = activeTimer, bit1 = hasTarget, bit0 = processQueue)

    if ((flagsByte >> 6 & 1) == 0) // Not in timed state
    {
        if (((flagsByte >> 1 & 1) != 0) && (this[0x6c] != 0)) // Has active target/component
        {
            // Call virtual function at vtable+0xdc (likely getTargetTransform or getCurrentAnimation)
            (**(code **)(*this + 0xdc))(this + 0xdf); // +0xdf is a local transform buffer (0xdf bytes? possibly alignment)
            bResult = FUN_00481620(); // Some condition check (e.g., isPaused, isReady)
            if (bResult != '\0')
            {
                pad1 = 0;
                pad2 = 0;
                pad3 = 0;
                pad4 = _DAT_00d5780c; // Global constant (maybe identity quaternion or zero)
                // Build transform from target component's +0xe0 offset
                FUN_00544180(this[0x6c] + 0xe0, localBuffer); // Construct transform from component data
                // Apply the transform via virtual function at vtable+0x28
                (**(code **)(*this + 0x28))(localBuffer);
            }
            FUN_0070acb0(); // Update related state (e.g., animation blending)
        }
        if ((*(byte *)((int)this + 0x39e) & 1) != 0) // Queue processing flag
        {
            iVar1 = this[0xd4]; // Current queue index (offset 0x350)
            do
            {
                if ((uint)this[0xd2] <= (uint)this[0xd4]) break; // 0xd2 = queue count (offset 0x348)
                iVar4 = *(int *)(this[0xd1] + this[0xd4] * 8); // 0xd1 = pointer to queue array (offset 0x344)
                if ((iVar4 != 0) && (iVar4 = iVar4 + -0x48, iVar4 != 0)) // Adjust to get object pointer (subtract 0x48)
                {
                    FUN_0070c130(iVar4, 0); // Process queue item (likely destruction or removal)
                }
                this[0xd4] = this[0xd4] + 1;
            } while ((uint)(this[0xd4] - iVar1) < 5); // Process at most 5 items per tick
            if (this[0xd4] == this[0xd2]) // Queue fully processed
            {
                FUN_0070b300(); // Signal queue completion
            }
        }
    }
    else // Timed state active (bit6 set)
    {
        fTimer = (float)this[0xc4] - DAT_012067e8; // Subtract delta time (global frame time)
        this[0xc4] = (int)fTimer;
        if (fTimer <= 0.0)
        {
            FUN_004088c0(this + 0xf); // Destroy this object (free memory at +0xf offset)
            return;
        }
    }
}