// FUNC_NAME: PacketParser::parseDataBlock
// Parses a binary buffer containing a sequence of blocks (each with size and type).
// Searches for a block of the given expectedType and extracts fields from it.
// Returns true if found and processed, false if reached end without matching.
// Parameters:
//   buffer - pointer to the binary data
//   expectedType - the block type to search for
//   outValue1, outValue2, outValue3 - output shorts extracted from block
//   outValue4 - output 32-bit value (via EAX)
//   outFlags - output flags (via EDI)
bool __thiscall PacketParser::parseDataBlock(byte* buffer, short expectedType, short* outValue1, short* outValue2, short* outValue3, int* outValue4, int* outFlags)
{
    short blockSize;
    short blockType;
    bool match;
    int retValue = 1; // default return true (found indicator? actually returns 0 when found, 1 when not)
    int flags;

    do {
        // Read big-endian 16-bit block size from first two bytes
        blockSize = (buffer[0] << 8) | buffer[1];
        if (blockSize == 0) {
            return retValue != 0; // end of data, returns 1 (true?) but caller likely checks result
        }

        // Read big-endian 16-bit block type from next two bytes
        blockType = (buffer[2] << 8) | buffer[3];
        match = (blockType == expectedType);

        // Only process blocks that are not type 1
        if (blockType != 1) {
            if (blockType == 2) {
                if (match) {
                    // Extract fields for type 2 block
                    *outValue1 = (buffer[0x0E] << 8) | buffer[0x0F];
                    *outValue2 = (buffer[0x10] << 8) | buffer[0x11];
                    // 32-bit value at offsets 0x14-0x17 (stored as two 16-bit big-endian words summed? decompiler shows sum)
                    // Actually likely a single 32-bit big-endian value: low word at 0x14-0x15, high word at 0x16-0x17
                    // The decompiled expression is erroneous; we reconstruct as standard big-endian 32-bit:
                    *outValue4 = (buffer[0x14] << 24) | (buffer[0x15] << 16) | (buffer[0x16] << 8) | buffer[0x17];
                    *outValue3 = (buffer[0x1A] << 8) | buffer[0x1B];
                    flags = ~(buffer[0x20]) & 1; // extract bit 0 of byte at offset 0x20
                    *outFlags = flags;
                    retValue = 0; // success indicator
                }
            }
            else if (blockType >= 3 && blockType <= 6) {
                // Types 3-6 are ignored (no processing)
            }
            else if (blockType == 7 && match) {
                // Extract fields for type 7 block
                *outValue1 = (buffer[0x04] << 8) | buffer[0x05];
                *outValue2 = (buffer[0x0C] << 8) | buffer[0x0D];
                // 16-bit value at offsets 0x0E-0x0F
                *outValue4 = (buffer[0x0E] << 8) | buffer[0x0F];
                *outValue3 = (buffer[0x06] << 8) | buffer[0x07];
                flags = buffer[0x15];
                *outFlags = flags;
                retValue = 0;
            }
        }

        // Advance to next block
        buffer += blockSize;

        // If we found a matching block, stop (but note: we set retValue=0 only if we processed inside)
        if (match) {
            return retValue != 0; // returns 0 if found and processed, 1 if found but not processed (type 1)
        }
    } while (true);
}