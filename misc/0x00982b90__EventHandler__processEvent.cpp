// FUNC_NAME: EventHandler::processEvent
void __thiscall EventHandler::processEvent(EventHandler* this, uint* eventFlags)
{
    // +0x68: pointer to current event handler context
    void* handlerContext = *(void**)((uint)this + 0x68);
    
    // Check if there is an existing handler and the "cancel" flag (bit 3) is set
    if (handlerContext != nullptr && ((*eventFlags >> 3) & 1) != 0)
    {
        // +0x14: callback function pointer within handler context
        void (*callback)(undefined4, void*, int) = *(void (__thiscall**)(undefined4, void*, int))((uint)handlerContext + 0x14);
        if (callback != nullptr)
        {
            // The callback receives a context value (+0x8), the handler pointer, and a trigger code 1
            callback(*(undefined4*)((uint)handlerContext + 8), handlerContext, 1);
        }
        // Clear the stored handler
        *(void**)((uint)this + 0x68) = nullptr;
    }
    
    // If the flag is not set, delegate to another handler and return
    if (((*eventFlags >> 3) & 1) == 0)
    {
        // FUN_00982520 likely clears or processes the event flags
        EventHandler::clearEvent(eventFlags);
        return;
    }
    
    // Otherwise store the event flags as the new handler and register a static callback
    *(uint**)((uint)this + 0x68) = eventFlags;
    // +0x10: likely a pointer to a state machine or event dispatcher that manages the callback
    EventHandler::registerStaticHandler((uint)this + 0x10, &LAB_00982b20, 1);
}