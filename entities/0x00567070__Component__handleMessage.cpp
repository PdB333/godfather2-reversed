// FUNC_NAME: Component::handleMessage
// Address: 0x00567070
// Role: Handles incoming messages for a component, including a special destroy message (-0xDC).

void __thiscall Component::handleMessage(int param_2) {
    if (param_2 == -0xDC) {
        cleanupInternal();  // FUN_00566b70: internal cleanup routine
        if (this->destroyablePtr_0x11c != 0) {
            releasePointer(this->destroyablePtr_0x11c);  // FUN_009c8eb0: release/free pointer
            this->destroyablePtr_0x11c = 0;
        }
        this->flags_0x2c |= 0x400;  // mark destroyed
        this->state_0x10 = 13;      // set to destroyed state
        return;
    }

    // Forward message to optional custom handler
    if (this->messageHandler_0x58 != 0) {
        this->messageHandler_0x58(param_2);
    }

    // Notify global singleton (e.g., engine or manager)
    if (gGlobalObject != 0) {
        ((void (*)())(*(int *)(*gGlobalObject + 0xc)))();  // call virtual function at offset 0xc
    }

    // Delegate to child component if present
    if (this->childComponent_0xc != 0) {
        // Second virtual method (offset 4) called with 'this' as argument
        this->childComponent_0xc->virtualMethod2(this);
        this->childComponent_0xc = 0;  // release reference
    }

    // Store the message and update state
    this->storedMessage_0x18 = param_2;
    this->flag_0x14 = 1;
    this->state_0x10 = 9;  // transition to processing state
}