// FUNC_NAME: TimerManager::update
void __thiscall TimerManager::update(int this, float deltaTime)
{
    uint32_t flags;
    volatile uint32_t* errorFlag;
    int action;
    float holdTimer;
    float durationTimer;
    float someFloat;

    // Decrement hold timer at +0x4c
    holdTimer = *(float*)(this + 0x4c);
    if (holdTimer > 0.0f)
    {
        holdTimer -= deltaTime;
        *(float*)(this + 0x4c) = holdTimer;
        if (holdTimer < 0.0f)
        {
            // Hold timer expired: set bit 31 of flags (+0x2c) and reset timer
            *(uint32_t*)(this + 0x2c) |= 0x80000000;
            *(float*)(this + 0x4c) = 0.0f;
        }
    }

    flags = *(uint32_t*)(this + 0x2c);

    if ((flags & 1) == 0) // Bit 0 not set (not paused)
    {
        if ((int32_t)flags < 0) // Bit 31 set (hold timer expired)
        {
            // If no pending action (+0x38 is null), set error flag via TLS
            if (*(int32_t*)(this + 0x38) == 0)
            {
                // Access thread-local error flag:
                // FS:[0x2c] -> pointer -> offset +8 -> value at that address is set bit 0
                errorFlag = (volatile uint32_t*)(*(int32_t*)(this + 0x10) + *(int32_t*)(**(int32_t**)(0x2c) + 8));
                *errorFlag |= 1;
            }
        }
        else // Bit 31 not set (normal state)
        {
            // Decrement duration timer at +0x30
            durationTimer = *(float*)(this + 0x30) - deltaTime;
            *(float*)(this + 0x30) = durationTimer;
            if (durationTimer <= 0.0f)
            {
                // Duration timer expired
                if ((*(uint32_t*)(*(int32_t*)(this + 0x28) + 0x24) & 0x40000000) == 0)
                {
                    action = GetNextAction(); // FUN_004fe350
                    if (action != 0)
                    {
                        durationTimer = *(float*)(*(int32_t*)(this + 0x28) + 0x8c);
                        someFloat = durationTimer;
                        UpdateGlobalState(); // FUN_004e41b0 (side effect)
                        *(float*)(this + 0x30) = durationTimer - someFloat * durationTimer * g_someConstant; // DAT_00e2cd54
                        ExecuteAction(this, action); // FUN_004fd910
                    }
                }
                else
                {
                    durationTimer = *(float*)(*(int32_t*)(this + 0x28) + 0x8c);
                    someFloat = durationTimer;
                    UpdateGlobalState(); // FUN_004e41b0
                    *(float*)(this + 0x30) = durationTimer - someFloat * durationTimer * g_someConstant;
                    ExecuteAction(this, 0); // FUN_004fd910 with zero action
                }
            }
        }

        // Update child actions (count at +0x3c)
        int childCount = *(int32_t*)(this + 0x3c);
        for (int i = 0; i < childCount; i++)
        {
            UpdateChildAction(deltaTime); // FUN_004fdce0
        }
    }
    else // Bit 0 set (paused)
    {
        if ((int32_t)flags < 0) // Bit 31 also set -> set error and early exit
        {
            errorFlag = (volatile uint32_t*)(*(int32_t*)(this + 0x10) + *(int32_t*)(**(int32_t**)(0x2c) + 8));
            *errorFlag |= 1;
            return;
        }
        // If bit 0 set but bit 31 not set, fall through to end
    }
}