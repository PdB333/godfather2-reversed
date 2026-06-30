// FUNC_NAME: compare20ByteKey
bool __fastcall compare20ByteKey(short *key1, short *key2)
{
    // Compare two 20-byte structures:
    // Offset 0: short (2 bytes)
    // Offset 2: short (2 bytes)
    // Offset 4: int (4 bytes)
    // Offset 8: int (4 bytes)
    // Offset 12: int (4 bytes)
    // Offset 16: int (4 bytes)
    // Total 20 bytes

    if ((*key1 != *key2) || (key1[1] != key2[1]))
        return false;

    int *intKey1 = (int *)(key1 + 2);
    int *intKey2 = (int *)(key2 + 2);

    if (intKey1[0] != intKey2[0]) return false;
    if (intKey1[1] != intKey2[1]) return false;
    if (intKey1[2] != intKey2[2]) return false;
    if (intKey1[3] != intKey2[3]) return false;

    return true;
}