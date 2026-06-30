// FUNC_NAME: InputManager::processInputSlot(uint index)
// Function address: 0x005378e0
// Reads touch/pointer input from a global array of 0x38-byte entries (max 0x1000 indices).
// Each entry contains a 2-byte X at offset 0x02 and 2-byte Y at offset 0x04.
// Converts to floats and passes to a position update routine, then optionally calls a flush function.

void InputManager::processInputSlot(uint index) {
    uint8_t* entryPtr;

    // Clamp index to the global touch buffer size: 0x1000 entries, each 0x38 bytes
    if (index < 0x1000) {
        // DAT_011a0f28 is the base of the input slot array
        entryPtr = &DAT_011a0f28 + index * 0x38;
    } else {
        entryPtr = NULL;
    }

    // Read 16-bit integer values at +0x02 (X) and +0x04 (Y) and convert to floats
    float x = (float)*(uint16_t*)(entryPtr + 2);
    float y = (float)*(uint16_t*)(entryPtr + 4);

    // Pack into a 2-element float array for the position update call
    float coords[2] = { x, y };

    // Update the cursor/pointer position
    // DAT_0121a394 - likely a global display device handle
    // *(uint32*)(DAT_0121b0ac + 0x20) - field in the InputManager singleton at offset 0x20 (maybe current viewport)
    FUN_0060ac80(DAT_0121a394, *(uint32*)(DAT_0121b0ac + 0x20), coords);

    // If the singleton's +0x08 flag is set (e.g. "active" or "dirty"), perform additional commit/flush
    if (*(int*)(DAT_0121b0ac + 0x08) != 0) {
        FUN_006063b0();
    }
}