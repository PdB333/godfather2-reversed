// FUNC_NAME: Mission::setFlags
// Function address: 0x0084fa30
// Role: Sets a bitmask of flags on this mission object, with state-dependent behavior.
// If state is 3 (ready), it calls a callback (if set) and transitions to state 4.
// If state is non-zero but not 3, it just ORs the flags.
// If state is 0, it returns 0 (failure).

int __thiscall Mission::setFlags(uint flags)
{
    // +0x84: current state (0 = inactive, 3 = ready, 4 = active, etc.)
    int state = *(int *)(this + 0x84);

    if (state == 3)
    {
        // +0x98: pointer to a callback object with a virtual function at vtable+8
        void* callbackObj = *(void**)(this + 0x98);
        if (callbackObj != nullptr)
        {
            // Call the third virtual function (index 2) on the callback object
            (**(code**)(**(int**)callbackObj + 8))();
        }
        // +0x88: bitmask of flags
        *(uint*)(this + 0x88) |= flags;
        // Transition to state 4 (active)
        *(int*)(this + 0x84) = 4;
        return 1;
    }

    if (state != 0)
    {
        // Non-zero state (but not 3): just OR the flags, keep state unchanged
        *(uint*)(this + 0x88) |= flags;
        return 1;
    }

    // State is 0: cannot set flags, return failure
    return 0;
}