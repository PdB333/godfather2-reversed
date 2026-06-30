// FUNC_NAME: StateMachine::handleStateTransition
// Address: 0x0063dbf0
// This function handles state transitions, specifically entering or processing a "processing" state (0x11F = 287).
// It copies a source value, checks the current state, and either transitions to the processing state or calls
// a processing function on transition data.
// Offsets:
// +0x04: sourceData (some input data)
// +0x08: backupData (copy of sourceData)
// +0x0C: previousState (stores the old state before transition)
// +0x10: processingData (data passed to the processing function)
// +0x14: currentState (the current state ID)
// +0x18: pendingProcessingData (new data used when entering processing state)

#define STATE_PROCESSING 0x11F

int __thiscall StateMachine::handleStateTransition(void* thisPtr, undefined4 param_1)
{
    StateMachine* self = (StateMachine*)thisPtr;

    // Backup the source data
    self->backupData = self->sourceData;

    if (self->currentState != STATE_PROCESSING)
    {
        // Save the old state and transition into processing state
        self->previousState = self->currentState;
        self->currentState = STATE_PROCESSING;
        // Load the pending processing data
        self->processingData = self->pendingProcessingData;
        return 1; // Transition succeeded
    }

    // Already in processing state – call the processing function on the current data
    self->previousState = FUN_00639c70(self->processingData, param_1);
    return 1;
}