// FUNC_NAME: MultiTrackStream::decrementPosition
int __thiscall MultiTrackStream::decrementPosition(void) {
    int size;
    int newIndex;
    int currentIndex;

    // Check if the stream is initialized (likely checks a valid flag or pointer)
    if (!FUN_00579170()) { // Could be isInitialized() or similar
        return 0;
    }

    // Possibly lock or update state
    FUN_00582090(); // Could be lock() or updateInternalState()

    // Read size at offset +0x2e4
    size = *(int *)(this + 0x2e4); // +0x2e4: buffer size (number of elements)
    // Read current index at offset +0x2e8
    currentIndex = *(int *)(this + 0x2e8); // +0x2e8: current read position index

    // Decrement index with wrap-around: (currentIndex - 1 + size) % size
    newIndex = currentIndex - 1 + size;
    *(int *)(this + 0x2e8) = newIndex % size; // Update index

    // Set valid flag and update current data pointer
    *(int *)(this + 0x2c) = 1; // +0x2c: valid flag (1 = valid)
    *(int *)(this + 0x18) = *(int *)(this + 0x2e0); // +0x18: current data pointer; +0x2e0: base data pointer

    // Return success code (0x01000000) – always non-zero on success
    // The quotient (newIndex / size) is 0 if we wrapped, 1 otherwise, but shifted right 8 bits yields 0.
    // So the return value is always 0x01000000.
    return 0x01000000;
}