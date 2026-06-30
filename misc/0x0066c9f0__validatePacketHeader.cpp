// FUNC_NAME: validatePacketHeader
// Function at 0x0066c9f0: Validates a received packet header from EA EARS networking (libtomcrypt packet.c style).
// Checks: length < 0x93, type == 0x02, and the ID byte matches expectedId.
// Returns 0 on success, 7 on failure.
int validatePacketHeader(const uchar* packet, uint expectedId)
{
    // Packet header structure (little-endian):
    //   +0: uint16 length
    //   +2: uint8 type
    //   +3: uint8 id
    // Length must be < 0x93, type must be 0x02, id must match expected.

    if (packet == NULL) {
        // Debug assertion from libtomcrypt: failure on line 23 of ..\src\libtomcrypt\packet.c
        int argCheckResult = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n",
                                          "src != NULL", 0x17, "..\\src\\libtomcrypt\\packet.c");
        _fprintf((FILE*)(argCheckResult + 0x40), "_ARGCHK '%s' failure on line %d of file %s\n",
                 "src != NULL", 0x17, "..\\src\\libtomcrypt\\packet.c");
    }

    // Read the packet header fields (unaligned)
    uint16 length = *(const uint16*)packet;
    uint8 type = packet[2];
    uint8 id = packet[3];

    if (length < 0x93 && type == 0x02 && (uint)id == expectedId) {
        return 0; // CRYPT_OK
    }
    return 7; // CRYPT_INVALID_PACKET (or similar error code)
}