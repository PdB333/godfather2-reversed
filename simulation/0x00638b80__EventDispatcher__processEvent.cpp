// FUNC_NAME: EventDispatcher::processEvent
void __thiscall EventDispatcher::processEvent(void *this, uint eventData) 
{
    int handlerIndex;
    int *handlerTable;
    
    // this+0x0: vtable? (not used)
    // this+0x4: target object for dispatch
    // this+0x8: ?
    // this+0xC: event type ID
    // this+0x10: pointer to extra data (for type 0x116)
    // this+0x28: pointer to pointer (for types 0x11D/0x11E)
    // this+0x? ...
    
    uint eventType = *(int *)((char *)this + 0xC);
    
    if (eventType == 0x116) {
        // Special case: compute handler index from direct pointer + offset
        handlerIndex = *(int *)((char *)this + 0x10) + 0x10;
    }
    else if ((eventType - 0x11dU) < 2) { // types 0x11D and 0x11E
        // Dereference double pointer at +0x28
        handlerIndex = **(int **)((char *)this + 0x28);
    }
    else if (eventType < 0x101) {
        // Convert low type ID to string name (debug?) and then to index
        handlerIndex = FUN_00636c00(&DAT_00e4242c, eventType);
    }
    else {
        // Look up in global table of handlers by type
        handlerIndex = *(int *)(&DAT_00e2a4bc + eventType * 4);
    }
    
    // Dispatch the event with the computed handler index and target
    FUN_00638b20(eventData, handlerIndex, *(int *)((char *)this + 4));
    
    // Debug breakpoint – possibly assert or debugger trap
    __asm { int 3 } // swi(3)
    
    return;
}