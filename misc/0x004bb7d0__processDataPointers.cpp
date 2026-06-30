// FUNC_NAME: processDataPointers
// Function at 0x004BB7D0: Iterates over a set of 7 pointers stored at specific offsets in a structure,
// passing each pointer's address and size 32 to a processing function (FUN_0064b810).
// The 'this' parameter is unused, suggesting this may be a static helper or a method called on a base context.
void processDataPointers(int unusedThis, int* pData)
{
    int* pCurrent;

    // Offset +0x04: first pointer
    pCurrent = (int*)*(pData + 1);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x08: second pointer
    pCurrent = (int*)*(pData + 2);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x0C: third pointer
    pCurrent = (int*)*(pData + 3);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x10: fourth pointer
    pCurrent = (int*)*(pData + 4);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x14: fifth pointer
    pCurrent = (int*)*(pData + 5);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x18: sixth pointer
    pCurrent = (int*)*(pData + 6);
    FUN_0064b810(32, &pCurrent);

    // Offset +0x1C: seventh pointer
    pCurrent = (int*)*(pData + 7);
    FUN_0064b810(32, &pCurrent);
}