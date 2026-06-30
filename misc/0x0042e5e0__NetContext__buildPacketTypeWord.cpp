// FUNC_NAME: NetContext::buildPacketTypeWord
uint __fastcall NetContext::buildPacketTypeWord(byte packetTypeSelector, uint extraFlags) {
    // Get pointer to per-thread network context from TLS (FS:[0x2C])
    NetContext* context = *(NetContext**) (__readfsdword(0x2C)); // TLS slot for network context

    ushort packetTypeBase = 0;

    // Select the base packet type from the table based on which bit is set in packetTypeSelector
    // The table entries are at offsets +0x10 through +0x1E (8 entries)
    if ((packetTypeSelector & 4) != 0) { // bit 2
        packetTypeBase = context->packetTypeTable[2]; // +0x14
    } else if ((packetTypeSelector & 8) != 0) { // bit 3
        packetTypeBase = context->packetTypeTable[3]; // +0x16
    } else if ((packetTypeSelector & 0x10) != 0) { // bit 4
        packetTypeBase = context->packetTypeTable[4]; // +0x18
    } else if ((packetTypeSelector & 0x20) != 0) { // bit 5
        packetTypeBase = context->packetTypeTable[5]; // +0x1A
    } else if ((packetTypeSelector & 0x40) != 0) { // bit 6
        packetTypeBase = context->packetTypeTable[6]; // +0x1C
    } else if ((char)packetTypeSelector < 0) { // bit 7 (signed check)
        packetTypeBase = context->packetTypeTable[7]; // +0x1E
    } else if ((packetTypeSelector & 1) != 0) { // bit 0
        packetTypeBase = context->packetTypeTable[0]; // +0x10
    } else if ((packetTypeSelector & 2) != 0) { // bit 1
        packetTypeBase = context->packetTypeTable[1]; // +0x12
    }

    // Apply additional flags from extraFlags
    if ((extraFlags & 0x400) != 0) {
        packetTypeBase |= context->flagHighTable; // +0x0C
    } else if ((extraFlags & 0x200) != 0) {
        packetTypeBase |= context->flagLowTable; // +0x0E
    }

    // Combine: low byte = original selector, high 16 bits = calculated type word
    return (uint)((packetTypeBase << 8) | packetTypeSelector);
}

// Structure offset documentation:
// NetContext (per-thread):
// +0x00: ...
// +0x0C: ushort flagHighTable; // OR this when extraFlags has 0x400
// +0x0E: ushort flagLowTable;  // OR this when extraFlags has 0x200
// +0x10: ushort packetTypeTable[0]; // selected by bit0 (1)
// +0x12: ushort packetTypeTable[1]; // selected by bit1 (2)
// +0x14: ushort packetTypeTable[2]; // selected by bit2 (4)
// +0x16: ushort packetTypeTable[3]; // selected by bit3 (8)
// +0x18: ushort packetTypeTable[4]; // selected by bit4 (0x10)
// +0x1A: ushort packetTypeTable[5]; // selected by bit5 (0x20)
// +0x1C: ushort packetTypeTable[6]; // selected by bit6 (0x40)
// +0x1E: ushort packetTypeTable[7]; // selected by bit7 (0x80)