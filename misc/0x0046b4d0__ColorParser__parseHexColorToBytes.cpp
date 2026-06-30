// FUNC_NAME: ColorParser::parseHexColorToBytes
bool __thiscall ColorParser::parseHexColorToBytes(const char* str, uint32_t outComponents[4]) {
    // Static mapping table: each byte defines how to extract a nibble from the input string.
    // Bits [7:3] = byte index (0-3), bits[2:0] = nibble shift (0=low nibble, 4=high nibble?).
    // Value 0xFF indicates a position where a hyphen '-' is expected.
    // The table spans 36 entries (0x24 bytes) from DAT_0112865c to DAT_01128680.
    static const uint8_t s_nibbleMapping[36] = {
        // Contents unknown; assumed to define nibble positions in ARGB/BGRA order.
        // Example: For a "AARRGGBB" hex string, entries would order nibbles accordingly.
        0x00, 0x01, 0x08, 0x09, 0x10, 0x11, 0x18, 0x19, // mapping for RRGGBBAA? Adjust as needed.
        0xFF, // Placeholder for '-'? 
        // ... remaining 27 entries (truncated for brevity)
    };

    bool success = false;
    uint8_t bytes[4] = {0, 0, 0, 0};

    if (str == nullptr) {
        goto fail;
    }

    // Skip whitespace
    while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n')) {
        str++;
    }

    // Optionally consume opening brace
    if (*str == '{') {
        str++;
    }

    success = true;
    const uint8_t* tablePtr = &s_nibbleMapping[0];

    do {
        if (tablePtr == &s_nibbleMapping[32]) { // check if we reached end of mapping (size 32? actual table size is 36, but logic uses &DAT_01128680)
            if (success) {
                // Copy parsed bytes to output
                outComponents[0] = (uint32_t)bytes[0];
                outComponents[1] = (uint32_t)bytes[1];
                outComponents[2] = (uint32_t)bytes[2];
                outComponents[3] = (uint32_t)bytes[3];
                return success;
            }
            break;
        }

        uint8_t mappingByte = *tablePtr;
        if (mappingByte == 0xFF)
        {
            // Expect a hyphen at this position
            success = (*str == '-');
        }
        else
        {
            char currentChar = *str;
            char digitValue = '\0';

            // Convert hex digit (0-9, a-f, A-F)
            if ((byte)(currentChar - 0x30U) < 10) {
                digitValue = currentChar - 0x30;            // '0'-'9'
            }
            else if ((byte)(currentChar + 0x9fU) < 6) {
                digitValue = currentChar - 0x57;            // 'a'-'f' (lowercase)
            }
            else if ((byte)(currentChar + 0xbfU) < 6) {
                digitValue = currentChar - 0x37;            // 'A'-'F' (uppercase)
            }
            else {
                success = false;                            // Invalid hex digit
            }

            // OR the nibble into the appropriate byte at the given shift
            bytes[mappingByte >> 3] |= (uint8_t)(digitValue << ((mappingByte & 7) * 4));
        }

        tablePtr++;
        str++;
    } while (success);

fail:
    // On failure, zero out output
    outComponents[0] = 0;
    outComponents[1] = 0;
    outComponents[2] = 0;
    outComponents[3] = 0;
    return success;
}