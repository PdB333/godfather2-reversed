// FUNC_NAME: SimManager::processPendingActions

// Address: 0x0071e420
// This function checks a pending flag (bit 0 of flags at +0x84) and if set,
// clears it and executes an action (processAction) followed by a global update.
// This pattern is typical for deferred processing in a simulation manager.

void __fastcall SimManager::processPendingActions(SimManager* this) {
    // +0x84: uint32 flags (bitfield)
    if ((this->flags & 1) != 0) {
        // Clear the pending bit
        this->flags &= ~1;
        // Execute the associated action (likely a member function)
        this->processAction();
        // Perform a global update (non-member function or static)
        globalUpdate();
    }
}