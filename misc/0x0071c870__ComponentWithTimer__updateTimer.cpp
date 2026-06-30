// FUNC_NAME: ComponentWithTimer::updateTimer
// Address: 0x0071c870
// Manages a countdown timer with random reset. Checks for a specific component and interface.

void __fastcall ComponentWithTimer::updateTimer(void* this)
{
    // +0x08: pointer to child component (or derived object)
    int* childComponent = *(int**)((char*)this + 0x08);
    // +0x30: float timer variable
    float* pTimer = (float*)((char*)this + 0x30);

    // Child must exist and not be a sentinel value (0x48 likely size or flag)
    if (childComponent != nullptr && childComponent != (int*)0x48)
    {
        // Compute base pointer by subtracting 0x48 (possibly to get parent structure)
        int* basePtr;
        if (childComponent == nullptr)
            basePtr = nullptr;
        else
            basePtr = (int*)((char*)childComponent - 0x48);

        // Virtual call at vtable index 4: query interface with ID 0x55859efa
        bool interfaceSupported = false;
        if (basePtr != nullptr)
        {
            typedef bool (__thiscall *QueryInterfaceFunc)(void*, uint);
            QueryInterfaceFunc queryFunc = *(QueryInterfaceFunc*)(*basePtr + 0x10);
            interfaceSupported = queryFunc(basePtr, 0x55859efa) != 0;
        }

        // Stack condition: check if some local address doesn't equal a global (likely debug/assert)
        // Also check bit 10 of a stack variable (in_stack_000008dc) – possibly flags
        if (interfaceSupported && (&stack0x00000000 != &DAT_00000004) && ((in_stack_000008dc >> 10 & 1) != 0))
        {
            if (*pTimer == DAT_00d5ccf8) // Constant, likely 0.0f
            {
                int randomValue = _rand();
                // unaff_retaddr likely came from a floating-point register (e.g., time delta)
                *pTimer = (float)randomValue * DAT_00e44590 * unaff_retaddr + 0.0f;
                FUN_0071c660(); // Common function, possibly updating dependent state
                return;
            }
            if (*pTimer < 0.0f)
            {
                *pTimer = 0.0f;
            }
            FUN_0071c660();
        }
    }
}