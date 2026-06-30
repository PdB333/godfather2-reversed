// FUNC_NAME: initArrayPairs
void __fastcall initArrayPairs(int thisPtr) {
    uint defaultVal = DAT_00e2b1a4;          // global constant
    uint* pairPtr = (uint*)(thisPtr + 0x10); // start of pair array (each pair = 2 DWORDs)
    int count = *(int*)(thisPtr + 0x0C);    // number of pairs to initialize

    for (int i = count; i > 0; --i) {
        *pairPtr = 0xFFFFFFFF;      // first element: -1 sentinel
        pairPtr[1] = defaultVal;    // second element: default value
        pairPtr += 2;               // advance to next pair
    }
}