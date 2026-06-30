// FUNC_NAME: UnknownClass::updateStateByFloatThreshold
void __thiscall updateStateByFloatThreshold(int thisPtr, float inputValue)
{
    int stateIndex;
    int stateValue;
    int outerStructBase;

    // Threshold comparison to select state
    if (inputValue <= _DAT_00d61fc8) // large threshold
    {
        if (inputValue <= DAT_00d5fb68) // medium threshold
        {
            if (inputValue <= DAT_00d5efd0) // small threshold
            {
                stateIndex = 1;
                stateValue = DAT_00e544ec;
            }
            else
            {
                stateIndex = 0;
                stateValue = DAT_00e544d8;
            }
        }
        else
        {
            stateIndex = 3;
            stateValue = DAT_00e544d4;
        }
    }
    else
    {
        stateIndex = 2;
        stateValue = DAT_00e544e0;
    }

    // Temporary variable (no-op assignment from global)
    int temp = uRam00000854;

    // Check if owner pointer at +0x04 is valid and not sentinel value 0x48
    int* ownerPtr = *(int**)(thisPtr + 4);
    if (ownerPtr != nullptr && ownerPtr != (int*)0x48)
    {
        // Convert pointer to base struct by subtracting 0x48 (offset to embedded object)
        outerStructBase = (int)ownerPtr - 0x48;

        // Check bit 25 at offset 0x1f58; if clear, proceed
        if ((*(uint*)(outerStructBase + 0x1f58) >> 0x19 & 1) == 0)
        {
            // Call helper function with the selected state index
            FUN_007fbdf0(stateIndex);

            // Write the selected state value to offset 0x80c in the outer struct
            *(int*)(outerStructBase + 0x80c) = stateValue;
            return;
        }
    }

    // Preserve global (does nothing)
    uRam00000854 = temp;
}