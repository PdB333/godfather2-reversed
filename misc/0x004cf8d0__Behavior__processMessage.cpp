// FUNC_NAME: Behavior::processMessage
// Address: 0x004cf8d0
// Role: Processes an incoming message/event for a behavior object. Validates state and triggers action via a lookup.

void __thiscall Behavior::processMessage(int *message) {
    int actionIndex;

    // Check if the message ID matches the expected action ID
    if (message[0] == this->m_expectedActionID) {
        // Conditions for readiness: flag bit 1 set, data pointer non-null,
        // all pending pointers are null, cooldown timer is -1,
        // and the message data's type field is non-null and not 0x48.
        if ((((((((this->m_flags & 2) != 0) &&
                (message[1] != 0)) &&
               (this->m_pendingAction1 == 0)) &&
              (this->m_pendingAction2 == 0 && this->m_pendingAction3 == 0)) &&
             (this->m_pendingAction4 == 0 &&
              (this->m_cooldownTimer == -1 && *(int *)(message[1] + 4) != 0)))) &&
            (*(int *)(message[1] + 4) != 0x48)) {
            // Derive action index from the message data's type field
            if (*(int *)(message[1] + 4) == 0) {
                actionIndex = 0;
            } else {
                actionIndex = *(int *)(message[1] + 4) - 0x48;
            }
            // Execute the action
            executeAction(actionIndex);
        }
        // Advance internal state / check next event
        advanceState();
    }
    // Free the message
    releaseMessage(message);
}