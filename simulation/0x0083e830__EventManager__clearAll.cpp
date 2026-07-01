// FUNC_NAME: EventManager::clearAll
void EventManager::clearAll()
{
    // Iterate over array of registered handlers at +0x100, count at +0x128
    // Each entry is a pair of uint32_t: [handlerPtr, ?]
    HandlerEntry* entries = reinterpret_cast<HandlerEntry*>(this + 0x100);
    int count = *(int*)(this + 0x128);
    HandlerEntry* end = entries + count;

    for (HandlerEntry* entry = entries; entry < end; ++entry)
    {
        // Call virtual function at vtable+0x18 on the handler object
        // First argument: owner context at +0xf8 (some reference)
        // Second argument: this manager
        IHandler* handler = reinterpret_cast<IHandler*>(entry->handlerPtr);
        handler->detach(*(void**)(this + 0xf8), this);
    }

    // Reset count to zero
    *(int*)(this + 0x128) = 0;

    // Notify system (0x13 = event code)
    FUN_008f67c0(0x13, this);

    // Release three consecutive objects at +0xdc, +0xe4, +0xec
    releaseObject(this + 0xdc);
    releaseObject(this + 0xe4);
    releaseObject(this + 0xec);

    // Reinitialize those objects (probably constructors)
    initObject(this + 0xdc);
    initObject(this + 0xe4);
    initObject(this + 0xec);

    // Reset global state (parameters: stop=0, reset=1)
    FUN_0083e4b0(0, 1);

    // Release object at +0xf4
    FUN_0043c200(*(void**)(this + 0xf4));

    // Free allocated resource at +0xd8
    if (*(int*)(this + 0xd8) != 0)
    {
        if (*(int*)(*(int*)(this + 0xd8) + 8) != 0)
        {
            FUN_009e7530(*(int*)(this + 0xd8));
        }
        FUN_009f01a0();
        *(int*)(this + 0xd8) = 0;
    }
}