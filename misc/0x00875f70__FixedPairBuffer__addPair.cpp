// FUNC_NAME: FixedPairBuffer::addPair
// Address: 0x00875f70
// Role: Adds a pair of 32-bit values to a fixed-size buffer (max 64 entries).
// Buffer layout: array of 64 entries, each 8 bytes (two uint32_t), starting at offset 0.
// Count stored at offset 0x200 (immediately after the buffer).
// Returns 1 on success, or (count & 0xffffff00) on failure (buffer full).

uint32_t __thiscall FixedPairBuffer::addPair(uint32_t* thisPtr, uint32_t* pair) {
    uint32_t count = thisPtr[0x80]; // offset 0x200 = 0x80 * 4 (since uint32_t)
    if (count < 0x40) { // max 64 entries
        thisPtr[count * 2] = pair[0];       // first element of pair
        thisPtr[count * 2 + 1] = pair[1];   // second element of pair
        thisPtr[0x80] = count + 1;           // increment count
        return 1;
    }
    return count & 0xffffff00; // buffer full, return error code
}