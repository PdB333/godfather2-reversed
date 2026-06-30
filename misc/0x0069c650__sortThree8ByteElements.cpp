// FUNC_NAME: sortThree8ByteElements
void sortThree8ByteElements(byte* a, byte* b, byte* c)
{
    // Sort three 8-byte elements in ascending order based on the first byte (key).
    // Each element is 8 bytes (two 4-byte values). The first byte is the sort key.
    // This is a sorting network: compare and swap pairs to ensure a <= b <= c.

    if (*b < *a)
    {
        // Swap a and b (8 bytes)
        uint32 temp0 = *(uint32*)b;
        uint32 temp1 = *(uint32*)(b + 4);
        *(uint32*)b = *(uint32*)a;
        *(uint32*)(b + 4) = *(uint32*)(a + 4);
        *(uint32*)a = temp0;
        *(uint32*)(a + 4) = temp1;
    }

    if (*c < *b)
    {
        // Swap b and c (8 bytes)
        uint32 temp0 = *(uint32*)c;
        uint32 temp1 = *(uint32*)(c + 4);
        *(uint32*)c = *(uint32*)b;
        *(uint32*)(c + 4) = *(uint32*)(b + 4);
        *(uint32*)b = temp0;
        *(uint32*)(b + 4) = temp1;
    }

    if (*b < *a)
    {
        // Swap a and b again (8 bytes)
        uint32 temp0 = *(uint32*)b;
        uint32 temp1 = *(uint32*)(b + 4);
        *(uint32*)b = *(uint32*)a;
        *(uint32*)(b + 4) = *(uint32*)(a + 4);
        *(uint32*)a = temp0;
        *(uint32*)(a + 4) = temp1;
    }
}