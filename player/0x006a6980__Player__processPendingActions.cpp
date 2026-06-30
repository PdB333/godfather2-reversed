// FUNC_NAME: Player::processPendingActions

// Function address: 0x006a6980
// Identified role: Process pending actions queued for this player (e.g., animation/behavior requests)
struct PendingAction {
    int actionId;          // +0x00: ID of the action to execute
    int64 paramA;          // +0x04: First parameter (e.g., start time or target)
    int64 paramB;          // +0x0C: Second parameter (e.g., duration or data)
    char processed;        // +0x14: Flag indicating this slot has been processed
    char pad[3];           // +0x15: Padding to 24 bytes
};

void __fastcall Player::processPendingActions() {
    // Check if any pending actions exist
    if (*(char*)(this + 0x9bc) == '\0')
        return;

    // Save current active action state
    int savedActionId = *(int*)(this + 0x6a4);          // +0x6a4
    int64 savedParamA   = *(int64*)(this + 0x6a8);      // +0x6a8
    int64 savedParamB   = *(int64*)(this + 0x6b0);      // +0x6b0

    int outputResult[2] = {0, 0};                       // local_20 – result from action execution

    PendingAction* entry = (PendingAction*)(this + 0x6bc); // +0x6bc: start of 32-slot queue
    for (int i = 0; i < 32; ++i, entry++) {
        if (entry->actionId != 0 && entry->processed == 0) {
            // Overwrite current action parameters with pending request
            *(int*)(this + 0x6a4)   = entry->actionId;
            *(int64*)(this + 0x6a8) = entry->paramA;
            *(int64*)(this + 0x6b0) = entry->paramB;

            // Execute the action (likely starts an animation, behavior, or triggers a state change)
            entry->processed = FUN_006a62a0(entry->actionId, outputResult, 0, 0);
        }
    }

    // Restore original action state (queued actions are one-shot; they don't persist)
    *(int*)(this + 0x6a4)   = savedActionId;
    *(int64*)(this + 0x6a8) = savedParamA;
    *(int64*)(this + 0x6b0) = savedParamB;

    // Clear the "has pending actions" flag
    *(char*)(this + 0x9bc) = 0;

    // If the action produced a result, handle it (e.g., enqueue result event)
    if (outputResult[0] != 0) {
        FUN_004daf90(outputResult); // Likely processes the action result
    }
}