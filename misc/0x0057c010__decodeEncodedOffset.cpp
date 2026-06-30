// FUNC_NAME: decodeEncodedOffset
// Function at 0x57c010: Decodes a relative offset from a compressed bitstream.
// Reads a nibble (type) from the first byte, then computes an offset based on type.
// Special cases: type 5 uses a 16-bit offset from bytes at +2; type 0xe uses a global base + (value+7>>3).
// Otherwise: offset = table1[type] + table2[type] * value.
// Returns pointer to the decoded data (base + offset).

extern int _UNK_00e2c2dc;       // global base for type 0xe
extern int DAT_00e2c2a4[16];    // table1 indexed by nibble type
extern int DAT_00e2c2e0[16];    // table2 indexed by nibble type

byte* decodeEncodedOffset(byte* buffer) // buffer in ESI
{
    uint type = *buffer & 0xf;
    uint value = ((uint)buffer[1] << 4) | ((uint)(*buffer >> 4));

    if (type == 5) {
        // 16-bit offset stored at buffer+2
        return buffer + *(ushort*)(buffer + 2);
    }
    if (type == 0xe) {
        // offset = global base + (value + 7) >> 3
        return buffer + _UNK_00e2c2dc + ((value + 7) >> 3);
    }
    // generic: offset = table1[type] + table2[type] * value
    return buffer + DAT_00e2c2a4[type] + DAT_00e2c2e0[type] * value;
}