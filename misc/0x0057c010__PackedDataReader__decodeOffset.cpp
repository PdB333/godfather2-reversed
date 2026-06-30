// FUNC_NAME: PackedDataReader::decodeOffset
// Function at 0x57c010: Decodes a variable-length offset from a packed data buffer.
// The buffer begins with a 2-byte header: first byte's low nibble = type (0-15),
// the high nibble of first byte combined with second byte forms a value.
// Depending on type, the offset to the next element is computed differently.
static byte* decodePackedOffset(byte* buffer)
{
    uint type = buffer[0] & 0xF;           // low nibble of first byte
    uint value = (buffer[0] >> 4) | (buffer[1] << 4); // high nibble+second byte -> 12-bit value

    if (type == 5)
    {
        // Direct 16-bit offset at offset 2
        return buffer + *(ushort*)(buffer + 2);
    }
    else if (type == 0xE)
    {
        // Global base offset + scaled value
        return buffer + _UNK_00e2c2dc + ((value + 7) >> 3);
    }
    else
    {
        // Table-driven: base offset array and multiplier array indexed by type
        return buffer + *(int*)(&DAT_00e2c2a4 + type * 4) + *(int*)(&DAT_00e2c2e0 + type * 4) * value;
    }
}