// FUNC_NAME: TNLConnection::isValidPacketType
bool __thiscall TNLConnection::isValidPacketType(int packetIndex)
{
    // this+0x0C points to a packet type info array (base)
    // The array contains a 4-byte header (e.g., count) and then entries.
    // Entry at base[1 + packetIndex] holds packet header bits.
    int* packetTypeArrayBase = *(int**)(this + 0x0C);
    uint packetHeaderBits = *(uint*)(packetTypeArrayBase + 1 + packetIndex);
    
    uint packetType = packetHeaderBits & 0x3F; // lower 6 bits encode packet type
    
    if (packetType > 0x18) {
        // Types 0x19-0x1B (25-27): return true only if bits 23-15 are clear (0xFF8000)
        if (packetType < 0x1C) {
            return (packetHeaderBits & 0xFF8000) == 0;
        }
        // Type 0x20 (32): always valid
        if (packetType == 0x20) {
            return true;
        }
    }
    // Types 0-24 and 28-31 are invalid, except type 32 already handled
    return false;
}