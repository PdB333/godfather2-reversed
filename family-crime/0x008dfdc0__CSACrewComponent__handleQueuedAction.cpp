// FUNC_NAME: CSACrewComponent::handleQueuedAction
void __fastcall CSACrewComponent::handleQueuedAction(int thisPtr) {
    // Call base class method (FUN_008db5d0)
    baseUpdate();

    // Check if the queued action hasn't been processed yet and is valid
    // +0x244: bool actionProcessed
    // +0x240: actionPtr (pointer to some action object)
    if (*(char*)(thisPtr + 0x244) == 0 && *(int*)(thisPtr + 0x240) != 0) {
        // Execute the action (FUN_00949dd0)
        executeAction(*(int*)(thisPtr + 0x240));
        // Mark as processed
        *(char*)(thisPtr + 0x244) = 1;
    }
}