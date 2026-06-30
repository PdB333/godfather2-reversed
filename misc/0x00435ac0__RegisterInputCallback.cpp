// FUNC_NAME: RegisterInputCallback
// Function at 0x00435ac0: Registers a handler entry with a fixed handler address (0x00439580) and a parameter.
// The handler entries are stored in a dynamic array managed by a global singleton (DAT_0122350c).
// The handler address is hardcoded, likely representing a specific message/callback type.
void __fastcall RegisterInputCallback(uint32_t param)
{
    // Get global manager pointer (assumed to be a pointer to a CallbackManager structure)
    CallbackManager* mgr = reinterpret_cast<CallbackManager*>(DAT_0122350c);

    // Check if we need to grow the dynamic array
    // Offsets: +0x1738 = array pointer (base of entries), +0x173c = count, +0x1740 = capacity
    if (mgr->handlerCount == mgr->handlerCapacity)
    {
        // Grow capacity: if zero, set to 1, else double
        uint32_t newCapacity = (mgr->handlerCapacity == 0) ? 1 : mgr->handlerCapacity * 2;
        // Reallocate the internal array (FUN_005e3000 handles resizing and updates mgr's internal state)
        // The function takes the new capacity (number of entries) as parameter.
        FUN_005e3000(newCapacity); // Assume this updates mgr->handlerArray and mgr->handlerCapacity
    }

    // Add the new entry at the current index
    uint32_t index = mgr->handlerCount;
    mgr->handlerCount++;

    // Each entry is 8 bytes: [handler pointer (4 bytes), param (4 bytes)]
    HandlerEntry* entry = &mgr->handlerArray[index];
    entry->handler = reinterpret_cast<void*>(0x00439580); // Fixed handler function/vtable
    entry->param   = param;
}