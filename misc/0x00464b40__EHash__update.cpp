// FUNC_NAME: EHash::update
// Function address: 0x00464b40
// Role: Updates a hash state by processing a single byte. Combines the byte with a base index,
// then uses the index to fetch a byte from a lookup table (array of 0x18-byte entries at +0x44),
// and returns a 32-bit value formed from the high three bytes of (index*3) and that table byte.
// This is likely part of a custom string hashing or CRC scheme used in the EARS engine.

uint32_t __thiscall EHash::update(uint8_t inputByte, uint32_t previousHash)
{
    // Update the hash index: signature * 15 + previousHash
    uint32_t index = inputByte * 15 + previousHash;
    // Read a byte from the table at +0x44, stride 0x18
    // The table is an array of 0x18-byte structures; we only need the first byte.
    uint8_t tableByte = *(uint8_t*)(this + 0x44 + index * 0x18);
    // Compute high part: ((index * 3) >> 8) & 0xFFFFFF, then shift left 8
    uint32_t highPart = ((index * 3) >> 8) & 0xFFFFFF;
    return (highPart << 8) | tableByte;
}