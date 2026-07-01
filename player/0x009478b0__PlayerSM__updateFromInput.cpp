// FUNC_NAME: PlayerSM::updateFromInput
void __thiscall PlayerSM::updateFromInput(int thisPtr, int inputData) {
    // inputData is a pointer to some input structure (e.g., PlayerInputData)
    // +0x20: pointer to data? Actually field at inputData+0x20 is checked for null.
    // If null, zero out four fields at this+0x58..0x64 (likely a vector: x, y, z, w)
    // Otherwise copy four values from inputData+0x20..0x2c into those fields.

    if (inputData == 0 || *(int*)(inputData + 0x20) == 0) {
        *(int*)(thisPtr + 0x64) = 0;   // +0x64: field4 (maybe w)
        *(int*)(thisPtr + 0x60) = 0;   // +0x60: field3 (maybe z)
        *(int*)(thisPtr + 0x5c) = 0;   // +0x5c: field2 (maybe y)
        *(int*)(thisPtr + 0x58) = 0;   // +0x58: field1 (maybe x)
    } else {
        // Copy 16 bytes from inputData+0x20 into this+0x58 (vector)
        *(int*)(thisPtr + 0x58) = *(int*)(inputData + 0x20);
        *(int*)(thisPtr + 0x5c) = *(int*)(inputData + 0x24);
        *(int*)(thisPtr + 0x60) = *(int*)(inputData + 0x28);
        *(int*)(thisPtr + 0x64) = *(int*)(inputData + 0x2c);

        // Get current time (or some timestamp) and store it
        uint timestamp = FUN_0043b490(); // likely returns game time in ms
        *(uint*)(thisPtr + 0x150) = timestamp; // +0x150: inputTimestamp

        // Set bit 3 in flags at +0x108 (indicates "new input received")
        *(uint*)(thisPtr + 0x108) |= 8;

        // If state ID at +0x54 is 1 (e.g., ground state)
        if (*(int*)(thisPtr + 0x54) == 1) {
            // If there is a sub-object pointer at +0x148 (e.g., vehicle or character)
            if (*(int*)(thisPtr + 0x148) != 0) {
                // Forward the input to that sub-object
                FUN_00949ce0(*(int*)(thisPtr + 0x148), inputData);
                return;
            }
            // Check flags: if bit 1 is set and bit 2 is clear (e.g., falling condition)
            if (((*(uint*)(thisPtr + 0x108) >> 1 & 1) != 0) &&
                ((*(uint*)(thisPtr + 0x108) >> 2 & 1) == 0)) {
                // Enter a special state (e.g., free fall)
                FUN_00947510();
                return;
            }
        }
    }
}