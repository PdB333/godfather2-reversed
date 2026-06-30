// FUNC_NAME: StateStack::popState
// Function address: 0x0063dd40
// Role: Pops a state from the state stack, restoring a previous state or pushing a new one.
// The stack stores state IDs and associated data. Constants 0x116 and 0x11f are likely enum values
// representing specific state types (e.g., kStateNamed and kStateEmpty).

undefined4 StateStack::popState(void)
{
    undefined4 savedData;
    
    // Assert that the current state ID is the expected named state (0x116)
    if (this->currentStateId != 0x116) {
        FUN_00638b80("<name> expected");
    }
    
    // Save the current state data before modifying
    savedData = this->currentStateData;
    
    // Copy the previous state pointer to the restored pointer slot
    this->restoredStatePointer = this->previousStatePointer;
    
    // Check if the next state ID is not the empty sentinel (0x11f)
    if (this->nextStateId != 0x11f) {
        // Restore the next state as the new current state
        this->currentStateData = this->nextStateData;
        this->currentStateId = this->nextStateId;
        // Mark the next state slot as empty
        this->nextStateId = 0x11f;
        return savedData;
    }
    
    // If next state is empty, create a new state from the current data
    this->currentStateId = FUN_00639c70(this + 0x10);
    return savedData;
}