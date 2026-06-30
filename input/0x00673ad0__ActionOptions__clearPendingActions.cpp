// FUNC_NAME: ActionOptions::clearPendingActions
void __thiscall ActionOptions::clearPendingActions(ActionOptions* this, bool clearPending) {
    // Call base class cleanup (likely clears some base flags)
    this->clearBaseActionSlots();

    // Reset active flag at +0x104
    *(int*)((char*)this + 0x104) = 0;

    if (clearPending) {
        // Handle first pending action at +0x118
        if (*(int*)((char*)this + 0x118) != 0 && *(int*)((char*)this + 0x30) != 0) {
            int basePtr = *(int*)((char*)this + 4);  // +4 likely points to base class
            if (*(int*)((char*)this + 0x118) == *(int*)((char*)basePtr + 0x48)) {
                // If the pending action matches the current active base action, just set flag
                *(int*)((char*)basePtr + 0x80) = 1;
            } else {
                // Otherwise release the action object
                this->releaseAction();
            }
            // Clear the pending action pointer
            *(int*)((char*)this + 0x118) = 0;
        }

        // Handle second pending action at +0x11c
        if (*(int*)((char*)this + 0x11c) != 0 && *(int*)((char*)this + 0x34) != 0) {
            this->releaseAction();
            *(int*)((char*)this + 0x11c) = 0;
        }
    }
}