// FUNC_NAME: Entity::releaseState
// Function address: 0x00894c90
// Role: Releases or cleans up a state/resource associated with the entity.
// Checks if the state pointer at +0x2c is non-null, and the state index at +0x38 is non-zero and not 0x48 (invalid).
// If conditions met, clears state, computes a new index, updates state, copies data from param_2, and releases a resource if present.

void __thiscall Entity::releaseState(int thisPtr, uint someParam)
{
    int stateIndex;
    byte buffer[20]; // local_1c, 20-byte buffer for state data
    int* resourceHandle; // local_8, pointer to resource to release

    // Check if state pointer exists, state index is non-zero, and state index is not the invalid sentinel 0x48
    if (*(int*)(thisPtr + 0x2c) != 0 && 
        *(int*)(thisPtr + 0x38) != 0 && 
        *(int*)(thisPtr + 0x38) != 0x48) 
    {
        // Clear state flags (parameter 0)
        clearState(0);

        // Compute new state index: if current state index is 0, use 0; otherwise subtract 0x48
        if (*(int*)(thisPtr + 0x38) == 0) {
            stateIndex = 0;
        } else {
            stateIndex = *(int*)(thisPtr + 0x38) - 0x48;
        }

        // Update state with new index and flag 1
        setStateIndex(stateIndex, 1);

        // Copy state data from someParam into local buffer
        copyStateData(someParam, buffer);

        // If resource handle is non-null, release it
        if (resourceHandle[0] != 0) {
            releaseResource(resourceHandle);
        }
    }
}