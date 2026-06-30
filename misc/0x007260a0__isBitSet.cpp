// FUNC_NAME: isBitSet
// Function at 0x007260a0: checks if a specific bit in a byte bitfield at offset +0x115 is set.
bool __thiscall isBitSet(int this, byte bitIndex) {
    // Read the byte at this+0x115 and test the bit at position (bitIndex & 0x1f).
    // Since only 8 bits exist in a byte, bitIndex beyond 7 will always yield 0.
    return (*(byte *)(this + 0x115) & (1 << (bitIndex & 0x1f))) != 0;
}