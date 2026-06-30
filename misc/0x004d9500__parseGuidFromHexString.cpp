// FUNC_NAME: parseGuidFromHexString
// 0x004d9500: Converts a GUID/UUID hex string (with dashes) into a 16-byte binary GUID.
// The string format is expected to have 36+1 characters (excluding leading null?), but the code reads starting from index 1.
// If the string is empty (per FUN_004d9400), returns a hardcoded default GUID [baad dbaa efbe efbe 555a c1ea 1109 1091].
// Byte order matches Microsoft GUID structure: Data1 LE, Data2 LE, Data3 LE, Data4 (big-endian order).

#include <cstdint>

typedef unsigned char byte;

// Forward declaration of the empty string check (address 0x004d9400)
static bool isEmptyString(const char* str);

static inline byte hexCharToNibble(char c) {
    // Convert uppercase to lowercase, then compute hex value
    if (c >= 'A' && c <= 'Z')
        c += 0x20;
    if (c >= '0' && c <= '9')
        return c - 0x30;
    else
        return c - 0x57;  // 'a' -> 10, etc.
}

static inline byte hexPairToByte(char c1, char c2) {
    byte hi = hexCharToNibble(c1);
    byte lo = hexCharToNibble(c2);
    return (hi << 4) | lo;
}

// param_1 : output 16-byte buffer (binary GUID)
// param_2 : input hex string (with dashes)
void __thiscall parseGuidFromHexString(byte* outGuid, const char* hexString) {
    // FUN_004d9400 likely checks for empty/null string
    if (isEmptyString(hexString)) {
        // Default GUID: BAADDBAA-EFBEEFBE-555AC1EA-11091091
        outGuid[0] = 0xba;
        outGuid[1] = 0xad;
        outGuid[2] = 0xdb;
        outGuid[3] = 0xba;
        outGuid[4] = 0xef;
        outGuid[5] = 0xbe;
        outGuid[6] = 0xef;
        outGuid[7] = 0xbe;
        outGuid[8] = 0x55;
        outGuid[9] = 0x5a;
        outGuid[10] = 0xc1;
        outGuid[11] = 0xea;
        outGuid[12] = 0x11;
        outGuid[13] = 0x09;
        outGuid[14] = 0x10;
        outGuid[15] = 0x91;
        return;
    }

    // Parse hex string (format: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)
    // Note: hexString[0] appears to be unused (possibly a prefix or length byte).
    // The offsets below follow the original decompiled logic.

    // Data1 (4 bytes, little‑endian)
    outGuid[3] = hexPairToByte(hexString[1], hexString[2]);
    outGuid[2] = hexPairToByte(hexString[3], hexString[4]);
    outGuid[1] = hexPairToByte(hexString[5], hexString[6]);
    outGuid[0] = hexPairToByte(hexString[7], hexString[8]);

    // Data2 (2 bytes, little‑endian)
    outGuid[5] = hexPairToByte(hexString[10], hexString[11]);
    outGuid[4] = hexPairToByte(hexString[12], hexString[13]);

    // Data3 (2 bytes, little‑endian)
    outGuid[7] = hexPairToByte(hexString[15], hexString[16]);
    outGuid[6] = hexPairToByte(hexString[17], hexString[18]);

    // Data4, first two bytes (stored in order)
    outGuid[8] = hexPairToByte(hexString[20], hexString[21]);
    outGuid[9] = hexPairToByte(hexString[22], hexString[23]);

    // Data4, remaining six bytes (stored in order)
    outGuid[10] = hexPairToByte(hexString[25], hexString[26]);
    outGuid[11] = hexPairToByte(hexString[27], hexString[28]);
    outGuid[12] = hexPairToByte(hexString[29], hexString[30]);
    outGuid[13] = hexPairToByte(hexString[31], hexString[32]);
    outGuid[14] = hexPairToByte(hexString[33], hexString[34]);
    outGuid[15] = hexPairToByte(hexString[35], hexString[36]);
}