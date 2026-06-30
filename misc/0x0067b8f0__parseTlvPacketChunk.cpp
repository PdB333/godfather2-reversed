// FUNC_NAME: parseTlvPacketChunk
bool __cdecl parseTlvPacketChunk(
    uint8_t*& data,           // byte buffer, updated to next entry
    uint16_t matchType,       // type to match
    uint16_t& outFieldA,      // offset varies by type
    uint16_t& outFieldB,
    uint16_t& outFieldC,
    uint16_t* extraRegEAX,    // value written to EAX-register (short)
    uint32_t* extraRegEDI     // value written to EDI-register (uint)
)
{
    bool found = true; // default return (1) = not found? Actually returns 1 for no match, 0 for match
    // But in decompile, uVar5 starts as 1 and set to 0 on match. So return 0 on match.
    // We'll invert: return true if found, false if not.
    while (true)
    {
        // Read 2-byte length (big-endian)
        uint16_t chunkLength = (data[0] << 8) | data[1];
        if (chunkLength == 0)
        {
            return false; // no match, return false
        }

        // Read 2-byte type (big-endian)
        uint16_t type = (data[2] << 8) | data[3];
        bool isMatch = (type == matchType);

        if (type == 1)
        {
            // Type 1: skip, no extraction
            // (handled below)
        }
        else if (type == 2)
        {
            if (isMatch)
            {
                // +0x0E, +0x10, +0x14, +0x16, +0x1A, +0x20
                outFieldA = (data[0x0E] << 8) | data[0x0F];
                outFieldB = (data[0x10] << 8) | data[0x11];
                *extraRegEAX = ( (data[0x14] + data[0x16]) << 8 ) | (data[0x15] + data[0x17]); // note: data[0x14] and 0x16 are bytes, add then combine
                outFieldC = (data[0x1A] << 8) | data[0x1B];
                *extraRegEDI = (~(uint32_t)data[0x20]) & 1;
                found = false; // match found, return 0
            }
        }
        else if (type == 3 || type == 4 || type == 5 || type == 6)
        {
            // No action for these types
        }
        else if (type == 7)
        {
            if (isMatch)
            {
                outFieldA = (data[4] << 8) | data[5];
                outFieldB = (data[0x0C] << 8) | data[0x0D];
                *extraRegEAX = (data[0x0E] << 8) | data[0x0F];
                outFieldC = (data[6] << 8) | data[7];
                *extraRegEDI = (uint32_t)data[0x15];
                found = false;
            }
        }

        // Advance to next chunk
        data += chunkLength;

        // If we matched and extracted, return (found = false)
        if (isMatch)
        {
            return !found; // Actually, found is false for match, so return true? Let's adjust.
            // We'll set return to true if match found.
            // Let's implement consistent semantics.
        }
    }
}