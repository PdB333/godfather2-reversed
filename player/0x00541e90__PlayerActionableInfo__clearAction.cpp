// FUNC_NAME: PlayerActionableInfo::clearAction
void __thiscall PlayerActionableInfo::clearAction(uint param_2) {
    // Offset +0x12c: byte flags (bit0 = action is active)
    byte* flags = (byte*)((uint)this + 0x12c);
    if (*flags & 1) {
        // Stop any pending animation/action (FUN_00541bb0)
        stopAllActions(0); // likely "stopAllActions" or similar
    }

    // Offset +0x20c: current action ID
    uint* currentActionId = (uint*)((uint)this + 0x20c);
    if (param_2 == *currentActionId) {
        // Offset +0x13c: pointer to an action controller with vtable
        ActionController* controller = *(ActionController**)((uint)this + 0x13c);
        // Call vtable+8 (index 2) – stops the action behavior
        controller->vtable->stopAction(0);

        // Offset +0x210: pointer to action data
        ActionData* actionData = *(ActionData**)((uint)this + 0x210);
        // Check if action data has an associated object at +0x10
        if (*(int*)((uint)actionData + 0x10) != 0) {
            // Release the associated object
            releaseObject(actionData);              // FUN_009f1b20
            decrementRefCount((int)actionData + 8); // FUN_009f1ad0
            processDeletions();                     // FUN_009f01a0
        }
        // Clear the associated object pointer
        *(int*)((uint)actionData + 0x10) = 0;
        processDeletions(); // FUN_009f01a0
        // Reset action ID
        *currentActionId = 0;
    }
}