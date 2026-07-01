// FUNC_NAME: unknownClass::processStateAction
void __thiscall SomeManager::processStateAction(void) {
    // Resolve the object pointer from a handle or reference stored at +0x50.
    // FUN_00849cf0 likely converts a stored handle (e.g., object ID) to a live pointer.
    UnknownObject* obj = (UnknownObject*)resolveObject(*(void**)(this + 0x50));
    if (obj != nullptr) {
        // +0x5c: current state/action index (0 = call handler, 1 = set flag)
        int state = *(int*)(this + 0x5c);
        if (state == 0) {
            // State 0: invoke a default action (e.g., complete, start, or reset).
            handleStateZeroAction();
            return;
        }
        if (state == 1) {
            // Set bit 0 in the object's flags field (+0x58) to indicate a pending state.
            obj->flags |= 1;  // +0x58: flags bitfield, bit0 = pending/active
        }
    }
}