// FUNC_NAME: StateManager::setEntry
void __thiscall StateManager::setEntry(int index, uint newState, uint newData)
{
    // Offsets: this+0x18 is start of array of 8-byte entries (state at +0, data at +4)
    uint *statePtr = (uint *)(this + 0x18 + index * 8);
    uint *dataPtr = (uint *)(this + 0x1C + index * 8);
    uint oldState = *statePtr;
    uint oldData = *dataPtr;

    // Only modify if current state is not 3 (locked or terminal state)
    if ((oldState & 0xFF) != 0x03) {
        *statePtr = newState;
        *dataPtr = newData;
    } else {
        // When state is 3, perform internal maintenance (likely a no-op in this context)
        // The decompiled loop with acStack_f and acStack_17 appears to be a compiler artifact or inlined function
        // that doesn't affect the member variables. The original intent is to leave the entry unchanged.
        // For completeness, we replicate the logic:
        char buffer[8]; // acStack_17
        char internal[11] = {}; // acStack_f, uninitialized in actual code
        for (int i = 0; i < 2; i++) {
            char c = -1;
            if (((newState & 0xFF) != 1 && (newState & 0xFF) != 3) ||
                (c = internal[i], c != -2)) {
                buffer[i] = c;
            }
        }
        // Note: buffer is never written back to the object, so effectively a no-op.
        // The original values are restored below.
        *statePtr = oldState;
        *dataPtr = oldData;
    }
}