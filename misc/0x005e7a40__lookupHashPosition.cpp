// FUNC_NAME: lookupHashPosition
uint32_t lookupHashPosition(uint32_t hashId, Vector3* outPosition) {
    // Global table base pointer (DAT_01223504). Structure layout:
    // +0x1c: byte count of entries (max 256)
    // +4: array of 256 pointers to entry structs (indexed by low byte of hashId)
    // Each entry struct:
    // +0x40: float x
    // +0x44: float y
    // +0x48: float z
    uint8_t entryCount = *(uint8_t*)(gHashTableBase + 0x1c);
    uint32_t xorValue = hashId ^ 0xad103100; // XOR with magic constant (deobfuscation)
    uint8_t index = (uint8_t)hashId; // Low byte used as bucket index
    uint32_t entryPtr = 0;
    bool found = false;

    // Bounds and existence check
    if ((xorValue < entryCount) && (entryCount != 0) && (index < entryCount)) {
        entryPtr = *(uint32_t*)(gHashTableBase + 4 + index * 4);
        if (entryPtr != 0) {
            found = true;
        }
    }

    if (found) {
        // Copy Vector3 data from entry struct offset 0x40
        outPosition->x = *(float*)(entryPtr + 0x40);
        outPosition->y = *(float*)(entryPtr + 0x44);
        outPosition->z = *(float*)(entryPtr + 0x48);
    }

    // Return value encoding: high 24 bits = xorValue >> 8, low byte = success flag
    return ( (xorValue >> 8) << 8 ) | (uint8_t)found;
}