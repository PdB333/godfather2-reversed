// FUNC_NAME: Presentation::updateCurrentState
// Function address: 0x00951ad0
// Role: Updates the current state of a Presentation object, handles state transitions, and invokes the update callback.

void __fastcall Presentation::updateCurrentState()
{
    uint prevIndex;
    int currentStateObj;
    int prevStateObj;

    // Resolve current state object from array (offset +0x64) using index (offset +0x80)
    currentStateObj = resolveIndexToObject(*(int*)(*(int*)((char*)this + 0x64) + *(int*)((char*)this + 0x80) * 4));
    
    // Clear notification flags or perform housekeeping
    clearNotificationFlags();
    
    // Check if there is a previous state index
    prevIndex = *(uint*)((char*)this + 0xa0);  // +0xA0: previous state index
    if (prevIndex != 0xFFFFFFFF && prevIndex < *(uint*)((char*)this + 0x68))  // +0x68: count of states
    {
        prevStateObj = resolveIndexToObject(*(int*)(*(int*)((char*)this + 0x64) + prevIndex * 4));
        if (prevStateObj != 0)
        {
            // Apply a presentation effect: pass a transform, ID, and global context
            applyPresentationEffect(*(int*)(prevStateObj + 0x48), (char*)prevStateObj + 0x10, 0, g_effectContext);
        }
    }
    
    // Store the current state object in the global state machine table
    g_stateMachineArray[0x1b] = currentStateObj;
    
    // Call the update function through the vtable or function pointer at offset 0x28
    // The global array stores both the vtable pointer (index 0) and state object pointers.
    (*(void (**)())(*(int*)g_stateMachineArray + 0x28))();
}