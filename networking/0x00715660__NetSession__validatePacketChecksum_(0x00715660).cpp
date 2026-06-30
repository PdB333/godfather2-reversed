// FUNC_NAME: NetSession::validatePacketChecksum (0x00715660)
// This function validates a packet checksum. It checks a flag in the connection state (offset +0x0C)
// and either performs a full checksum validation or returns a modified version of the raw checksum.

int __thiscall NetSession::validatePacketChecksum(
    uint32 rawChecksum,           // initial checksum value (in EAX on entry)
    const uint8* packetData,      // pointer to packet data buffer
    uint32 sequenceNumber,        // sequence number of the packet
    uint32 param4,                // unused parameter? (likely a flag or length)
    int param5,                   // 0 = validate, non-zero = skip verification
    uint32* outChecksum           // output parameter for the computed checksum
)
{
    uint32 uVar2;
    uint32 checksum;
    uint8 local_18[12];           // buffer for checksum context (12 bytes)
    uint8 local_c[12];            // buffer for final checksum computation

    *outChecksum = 0;
    uVar2 = rawChecksum >> 8;

    // Check if bit 1 (0x02) is set in the connection state flags at offset +0x0C.
    // If set, bypass full validation and return the masked checksum.
    if ((*(uint32*)(this + 0x0C) >> 1) & 1) {
        // Return rawChecksum with low byte cleared (preserve bits 8..31)
        return uVar2 << 8;
    }

    // Copy packet data into the local checksum context buffer
    FUN_00732460(local_18, packetData);

    // Compute initial checksum value from the context and sequence number
    checksum = FUN_00713960(local_18, sequenceNumber);
    *outChecksum = checksum;

    // If param5 is 0, attempt to verify the computed checksum
    if (param5 == 0) {
        uVar2 = FUN_00714450(packetData, checksum);
        if ((char)uVar2 == '\0') {
            // Verification failed, return the masked rawChecksum
            uVar2 = uVar2 >> 8;
            return uVar2 << 8;
        }
    }

    // Update checksum context and compute final checksum
    FUN_00712ff0(packetData, local_c);
    return FUN_007151e0(local_c, sequenceNumber, param5, packetData);
}