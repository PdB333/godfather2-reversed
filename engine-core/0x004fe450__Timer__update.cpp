// FUNC_NAME: Timer::update

void __thiscall Timer::update(float deltaTime)
{
    uint32 flags;
    uint32* errorFlagPtr;
    int returnVal;
    float tempFloat1;
    float tempFloat2;

    // Check if the delay timer (+0x4c) is active and decrement it
    if (*(float*)(this + 0x4c) > 0.0f)
    {
        *(float*)(this + 0x4c) -= deltaTime;
        if (*(float*)(this + 0x4c) < 0.0f)
        {
            *(uint32*)(this + 0x2c) |= 0x80000000;  // Set high bit (timer expired flag)
            *(float*)(this + 0x4c) = 0.0f;
        }
    }

    flags = *(uint32*)(this + 0x2c);
    if ((flags & 1) == 0)
    {
        if ((int)flags < 0)
        {
            // If the high bit is set (timer expired) and a special condition (+0x38 == 0)
            if (*(int*)(this + 0x38) == 0)
            {
                // Access a thread-local error flag (likely an assertion or logging mechanism)
                errorFlagPtr = (uint32*)(*(int*)(this + 0x10) + *(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8));
                *errorFlagPtr |= 1;
            }
        }
        else
        {
            // Normal timer tick: decrement the main timer (+0x30)
            *(float*)(this + 0x30) -= deltaTime;
            if (*(float*)(this + 0x30) <= 0.0f)
            {
                // Check a flag in the associated object (+0x28)
                if ((*(uint32*)(*(int*)(this + 0x28) + 0x24) & 0x40000000) == 0)
                {
                    returnVal = FUN_004fe350();  // Possibly a static or global function to query something
                    if (returnVal != 0)
                    {
                        tempFloat1 = *(float*)(*(int*)(this + 0x28) + 0x8c);
                        tempFloat2 = tempFloat1;
                        FUN_004e41b0();  // Unknown global or static
                        *(float*)(this + 0x30) = tempFloat1 - tempFloat2 * tempFloat1 * DAT_00e2cd54;  // Reset timer with a scaling factor
                        FUN_004fd910(this, returnVal);  // Process the return value
                    }
                }
                else
                {
                    tempFloat1 = *(float*)(*(int*)(this + 0x28) + 0x8c);
                    tempFloat2 = tempFloat1;
                    FUN_004e41b0();  // Same unknown call
                    *(float*)(this + 0x30) = tempFloat1 - tempFloat2 * tempFloat1 * DAT_00e2cd54;  // Reset timer
                    FUN_004fd910(this, 0);
                }
            }
        }

        // Loop over some count (+0x3c) calling a per-element update
        for (int i = 0; i < *(int*)(this + 0x3c); i++)
        {
            FUN_004fdce0(deltaTime);  // Update each element (perhaps children or subtimers)
        }
    }
    else if ((int)flags < 0)
    {
        // If low bit is set and high bit also set, set error flag and exit early
        errorFlagPtr = (uint32*)(*(int*)(this + 0x10) + *(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8));
        *errorFlagPtr |= 1;
        return;
    }
}