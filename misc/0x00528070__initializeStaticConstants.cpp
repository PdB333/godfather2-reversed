// FUNC_NAME: initializeStaticConstants
void initializeStaticConstants(void)
{
    // Call custom allocator to get 13 blocks of 4 bytes each (although code writes to 16 entries)
    // The allocator signature might be: (count, size, alignment, pool, flags) or similar
    int* table = (int*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    int constValue2 = DAT_00e2eff4; // global constant #2
    int constValue1 = DAT_00e2b1a4; // global constant #1

    if (table != nullptr) {
        // Fill a 16-element table with specific constant pattern
        table[0]  = constValue2;
        table[1]  = constValue1;
        table[2]  = 0;
        table[3]  = 0;
        table[4]  = constValue1;
        table[5]  = constValue1;
        table[6]  = constValue1;
        table[7]  = 0;
        table[8]  = constValue1;
        table[9]  = constValue2;
        table[10] = constValue1;
        table[11] = constValue1;
        table[12] = constValue2;
        table[13] = constValue2;
        table[14] = 0;
        table[15] = constValue1;

        // Possibly finalizes or registers the allocated table
        FUN_0060cde0();
    }
    // If allocation failed, just return (no side effects)
}