// FUNC_NAME: GUID::FromString
// Address: 0x004d9500
// Converts a GUID string (e.g., "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}") to 16-byte binary representation.
// If the input string is empty, fills with a debug pattern (0xBAADDBBAEFBEEF...).

class GUID {
public:
    // +0x00: 16-byte GUID data
    unsigned char data[16];

    // Converts a hex character to its numeric value (0-15)
    static unsigned char hexCharToNibble(char c) {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
        if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        return 0; // Should not happen with valid input
    }

    // Converts two hex characters to a byte
    static unsigned char hexPairToByte(char high, char low) {
        return (hexCharToNibble(high) << 4) | hexCharToNibble(low);
    }

    // Parse a GUID string (with braces and hyphens) into binary format
    // The string format: "{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}"
    // The binary format follows standard GUID byte order:
    //   bytes 0-3: first 4 hex digits (little-endian)
    //   bytes 4-5: next 2 hex digits (little-endian)
    //   bytes 6-7: next 2 hex digits (little-endian)
    //   bytes 8-15: last 8 hex digits (big-endian)
    void FromString(const char* str) {
        // Check if the string is empty (via external function at 0x004d9400)
        if (isStringEmpty(str)) {
            // Fill with debug pattern: BAADDBBA-EFBE-EFBE-...
            data[0] = 0xba;
            data[1] = 0xad;
            data[2] = 0xdb;
            data[3] = 0xba;
            data[4] = 0xef;
            data[5] = 0xbe;
            data[6] = 0xef;
            data[7] = 0xbe;
            data[8] = 0x55;
            data[9] = 0x5a;
            data[10] = 0xc1;
            data[11] = 0xea;
            data[12] = 0x11;
            data[13] = 0x09;
            data[14] = 0x10;
            data[15] = 0x91;
            return;
        }

        // Parse the GUID string, skipping the opening brace and hyphens
        // String indices: 0='{', 1-8=first group, 9='-', 10-13=second, 14='-', 15-18=third, 19='-', 20-23=fourth, 24='-', 25-36=fifth
        // Output byte order (little-endian for first three groups, big-endian for last):
        // data[3] = pair at str[1..2]
        // data[2] = pair at str[3..4]
        // data[1] = pair at str[5..6]
        // data[0] = pair at str[7..8]
        // data[5] = pair at str[10..11]
        // data[4] = pair at str[12..13]
        // data[7] = pair at str[15..16]
        // data[6] = pair at str[17..18]
        // data[8] = pair at str[20..21]
        // data[9] = pair at str[22..23]
        // data[10] = pair at str[25..26]
        // data[11] = pair at str[27..28]
        // data[12] = pair at str[29..30]
        // data[13] = pair at str[31..32]
        // data[14] = pair at str[33..34]
        // data[15] = pair at str[35..36]

        data[3] = hexPairToByte(str[1], str[2]);
        data[2] = hexPairToByte(str[3], str[4]);
        data[1] = hexPairToByte(str[5], str[6]);
        data[0] = hexPairToByte(str[7], str[8]);

        data[5] = hexPairToByte(str[10], str[11]);
        data[4] = hexPairToByte(str[12], str[13]);

        data[7] = hexPairToByte(str[15], str[16]);
        data[6] = hexPairToByte(str[17], str[18]);

        data[8] = hexPairToByte(str[20], str[21]);
        data[9] = hexPairToByte(str[22], str[23]);

        data[10] = hexPairToByte(str[25], str[26]);
        data[11] = hexPairToByte(str[27], str[28]);
        data[12] = hexPairToByte(str[29], str[30]);
        data[13] = hexPairToByte(str[31], str[32]);
        data[14] = hexPairToByte(str[33], str[34]);
        data[15] = hexPairToByte(str[35], str[36]);
    }

private:
    // External function at 0x004d9400 that checks if the string is empty
    bool isStringEmpty(const char* str);
};