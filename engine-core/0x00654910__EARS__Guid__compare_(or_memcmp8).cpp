// FUNC_NAME: EARS::Guid::compare (or memcmp8)
int __fastcall compareGuid(const void* firstBuffer, const void* secondBuffer)
{
    // Compare two 8-byte (or less) buffers. Returns 1 if equal, 0 if second > first, -256 if first < second.
    // Typically used for NetObjectId or GUID comparison.
    const uint8_t* first = (const uint8_t*)firstBuffer;
    const uint8_t* second = (const uint8_t*)secondBuffer;
    int remaining = 8; // total bytes to compare

    // Compare aligned 4-byte chunks first
    while (remaining >= 4)
    {
        if (*(const int32_t*)first != *(const int32_t*)second)
            goto byteCompare;
        first += 4;
        second += 4;
        remaining -= 4;
    }

    // All chunks matched
    if (remaining == 0)
        return 1; // equal

    // Fall back to byte-by-byte comparison for the last few bytes
byteCompare:
    {
        int diff = (int)(*first) - (int)(*second);
        if (diff != 0)
        {
            if (diff < 0)
                return -256; // 0xFFFFFF00
            return 0;        // first > second
        }
        if (remaining == 1)
            return 1; // equal (only one byte left and it matched)

        diff = (int)first[1] - (int)second[1];
        if (diff != 0)
        {
            if (diff < 0)
                return -256;
            return 0;
        }
        if (remaining == 2)
            return 1;

        diff = (int)first[2] - (int)second[2];
        if (diff != 0)
        {
            if (diff < 0)
                return -256;
            return 0;
        }
        if (remaining == 3)
            return 1;

        diff = (int)first[3] - (int)second[3];
        if (diff != 0)
        {
            if (diff < 0)
                return -256;
            return 0;
        }
        return 1; // equal (all four remaining bytes matched)
    }
}