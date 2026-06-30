// FUNC_NAME: computeHash (custom EA hash function, used extensively for 16-byte keys)

int computeHash(uint32_t* key) // key points to four 32-bit values (16 bytes)
{
    // Unknown: calls FUN_004d9af0 with the four key fields – possibly a CRC or initialization
    FUN_004d9af0(key[0], key[1], key[2], key[3]);

    // Hash over the key bytes using polynomial 0x1003f (sdbm-style variant)
    byte* bytePtr = (byte*)key;
    int hash = 0;

    do {
        hash = hash * 0x1003f + (uint32_t)*bytePtr;
        bytePtr++;
    } while (bytePtr < (byte*)(key + 4)); // hash exactly 16 bytes (stop at end of key struct)

    return hash;
}