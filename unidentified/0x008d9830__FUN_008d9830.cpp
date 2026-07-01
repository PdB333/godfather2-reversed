// FUNC_NAME: SomeClass::handleMessage
// Function address: 0x008d9830
// This function appears to be a message handler that first calls a base handler,
// then optionally forwards the call to a behavior component via a vtable call after a this-pointer adjustment.

void __thiscall SomeClass::handleMessage(uint param2, uint param3) {
    // Call base handler function (maybe common processing)
    baseMessageHandler(param2, param3);

    // Check conditions: flag at offset 400 must be zero, and the behavior pointer at offset 0x1b0
    // must be valid (non-null and not the sentinel 0x48).
    if (!this->blockedField && this->m_pBehavior != nullptr && this->m_pBehavior != (Behavior*)0x48) {
        Behavior* behavior = this->m_pBehavior;
        // The behavior pointer points to a derived object; the base class vtable is at offset -0x48.
        // Perform a virtual call at vtable offset 0x5c (method index 23) with adjusted 'this'.
        void* adjustedThis = (char*)behavior - 0x48;
        void (__thiscall* behaviorFunc)(void*, uint, uint) = 
            (void (__thiscall*)(void*, uint, uint))(*(int*)(*(int*)adjustedThis + 0x5c));
        behaviorFunc(adjustedThis, param2, param3);
    }
}