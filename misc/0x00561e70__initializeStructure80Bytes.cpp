// FUNC_NAME: initializeStructure80Bytes
void __thiscall initializeStructure80Bytes(int* thisPtr)
{
    // Clear all 20 DWORD fields (80 bytes) of the structure
    thisPtr[0] = 0;
    thisPtr[1] = 0;
    // Indices 2-3 are omitted but later indices cover all up to 0x13
    thisPtr[4] = 0;
    thisPtr[5] = 0;
    thisPtr[6] = 0;
    thisPtr[7] = 0;
    thisPtr[8] = 0;
    thisPtr[9] = 0;
    thisPtr[10] = 0;
    thisPtr[11] = 0;
    thisPtr[12] = 0;
    thisPtr[13] = 0;
    thisPtr[14] = 0;
    thisPtr[15] = 0;
    thisPtr[16] = 0;
    thisPtr[17] = 0;
    thisPtr[18] = 0;
    thisPtr[19] = 0; // +0x4C
}