// FUNC_NAME: TNL::BitStream::decodeCompressedBlock
void TNL::BitStream::decodeCompressedBlock(byte** streamPos, uint unused, int maxLength) {
    byte* cur = *streamPos;
    byte firstByte = *cur;
    byte lowNibble = firstByte & 0xF;

    if (lowNibble == 5) {
        // Compressed run-length encoded block
        uint count = (cur[1] << 4) | (firstByte >> 4); // number of entries
        // Compute the base pointer after fixed header: points to a location derived from cur+2 word
        byte* sequenceBase = (byte*)(*(ushort*)(cur + 2) + (int)(cur + 2) - 2);
        cur += 4; // skip header

        for (uint i = 0; i < count; i++) {
            byte entryFirst = *cur;
            uint length = (cur[1] << 4) | (entryFirst >> 4); // run length
            uint type = entryFirst & 0xF; // type identifier
            int index = length - 1;

            if (index >= maxLength) {
                // Out of bounds or special termination
                switch (type) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        if (type == 4) {
                            handleOpcode4(); // side effect (e.g., callback)
                        }
                        *streamPos = sequenceBase;
                        return;
                    case 6:
                    case 7:
                    case 0xD:
                        *streamPos = sequenceBase;
                        return;
                }
                *streamPos = sequenceBase;
                return;
            }
            maxLength -= index;
            // Advance cur by offset from tables based on type
            cur += (strides[type] * length) + baseOffsets[type];
        }
        *streamPos = cur;
    } else {
        // Single item (non-compressed)
        switch (lowNibble) {
            case 0:
                *streamPos = cur + 5;
                break;
            case 1:
                *streamPos = cur + 8;
                break;
            case 2:
                *streamPos = cur + 11;
                break;
            case 3:
                *streamPos = cur + 14;
                break;
            case 4:
                {
                    byte secondByte = cur[1];
                    handleOpcode4();
                    uint itemCount = (secondByte << 4) | (firstByte >> 4);
                    *streamPos = cur + (itemCount * 4) + 2;
                }
                break;
            case 6:
                {
                    uint offset = (cur[1] << 4) | (firstByte >> 4);
                    *streamPos = cur + offset + 8;
                }
                break;
            case 7:
                {
                    uint offset = (cur[1] << 4) | (firstByte >> 4);
                    *streamPos = cur + (offset * 2) + 8;
                }
                break;
            case 0xC:
                cur += 2; // skip two bytes, then fall through to default
                break;
            case 0xD:
                *streamPos = cur + 2;
                break;
            default:
                // Unknown opcode, just advance?
                break;
        }
        *streamPos = cur;
    }
}