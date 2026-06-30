// FUNC_NAME: NetSession::clearBit
void __thiscall NetSession::clearBit(uint bitIndex) {
    uint* wordPtr = (uint*)(this + 0x249c + (bitIndex >> 5) * 4); // Bitset array at +0x249c (32-bit words)
    *wordPtr &= ~(1 << (bitIndex & 0x1f));                       // Clear the bit at position bitIndex
}