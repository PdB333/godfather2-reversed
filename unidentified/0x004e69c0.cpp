// FUN_004e69c0: EARSObject::checkTriggerCondition
void EARSObject::checkTriggerCondition(int param_1) // ESI is implicit this (unaff_ESI in decompilation)
{
    // Check if this+0x28 is non-null (likely an active flag or pointer)
    if (*(int *)(this + 0x28) != 0)
    {
        // Compare global threshold with a float from param_1+0xC (e.g., distance or time)
        if (DAT_00e2af44 <= *(float *)(param_1 + 0xC))
        {
            // Read pointer at this+0x24, then flags byte at offset 0x14
            // Bit 0x20 indicates some triggerable state
            if ((*(byte *)(*(int *)(this + 0x24) + 0x14) & 0x20) != 0)
            {
                // Execute action twice (e.g., start/stop sound or animation)
                FUN_004e41b0();
                FUN_004e41b0();
            }
            // Finalize the trigger (e.g., mark as used or reset)
            FUN_004ef520();
        }
    }
}