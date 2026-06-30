// FUNC_NAME: getEncodedPropertyValue
int __fastcall getEncodedPropertyValue(uint encodedKey)
{
    uint mode = encodedKey & 0xC0000000;

    if (mode == 0)
    {
        // Mode 0: Return a bitmask based on bits 5-9 of the key.
        // Bits 5-9 select a bit position (0-31).
        return 1 << ((encodedKey >> 5) & 0x1F);
    }

    if (mode == 0x40000000)
    {
        // Mode 1: Return value from table at offset 8.
        // The key's lower bits (0-29) are used as an index into a 4-byte array.
        return *(int *)(encodedKey * 4 + 8);
    }

    if (mode == 0xC0000000)
    {
        // Mode 3: Return value from table at offset 0x54.
        // The key's lower bits (0-29) are used as an index into a 4-byte array.
        return *(int *)(encodedKey * 4 + 0x54);
    }

    // Mode 2 (0x80000000) or any other: return sentinel value.
    return -0x80000000;
}