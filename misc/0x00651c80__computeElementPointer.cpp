// FUNC_NAME: computeElementPointer
int computeElementPointer(int param1, int param2, int param3, int param4)
{
    // param1, param2: pointers (or indices) to define a range in a 4-byte-aligned array
    // param3, in_EAX (register value): another pair for a second range
    // param4: base pointer for the result
    // FUN_00652520 likely validates or clamps param3 (side effect ignored)
    FUN_00652520(param3);
    // Compute element count from param1 to param2 (each element is 4 bytes)
    int index1 = (param2 - param1) >> 2;
    // Compute element count from param3 to in_EAX (register value)
    int index2 = (in_EAX - param3) >> 2;
    // Return pointer to element at combined index offset from param4
    return param4 + (index1 + index2) * 4;
}