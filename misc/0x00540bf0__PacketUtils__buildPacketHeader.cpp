// FUNC_NAME: PacketUtils::buildPacketHeader
void __thiscall PacketUtils::buildPacketHeader(uint *packetHeader, uint packedFlagsAndSequence, uint param4, uint param5, uint param6, uint param7)
{
    // Build the first DWORD of the packet header:
    // Bits 0-4: packetType (from packedFlagsAndSequence low 5 bits)
    // Bits 5-9: constant 0x3E0 (likely packet version or flags)
    // Bits 16-27: sequence (from param2 high 12 bits shifted down? Actually param2 is the second parameter, but here param2 is packedFlagsAndSequence)
    // Note: The decompiled code shows param2 is used for low bits and param3 for high bits.
    // But we renamed: param2 -> packedFlagsAndSequence, param3 -> sequence
    // Actually in the original: *param1 = (param3 & 0xfff) << 0x10 | param2 & 0x1f | 0x3e0;
    // So param2 is the 5-bit field (packetType), param3 is 12-bit sequence number.
    // The signature shows uint params: param2, param3, param4, param5, param6, param7.
    // I'll preserve the original order: param1 is this, param2=packetType, param3=sequence, param4-7 are extra header fields.
    // So we adjust parameter names accordingly.
    packetHeader[0] = (param3 & 0xfff) << 16 | (param2 & 0x1f) | 0x3e0; // sequence in bits 16-27, packetType in bits 0-4, constant 0x3e0 in bits 5-9
    packetHeader[1] = param4;
    packetHeader[2] = param5;
    packetHeader[3] = param6;
    packetHeader[4] = param7;
}