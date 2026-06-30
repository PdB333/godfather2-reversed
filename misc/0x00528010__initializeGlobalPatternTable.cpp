// FUNC_NAME: initializeGlobalPatternTable
void initializeGlobalPatternTable(void)
{
    int* allocatedBlock;
    int value1;
    int value2;

    allocatedBlock = (int*)FUN_0060cd00(13, 4, 0, 1, 0); // allocate 8 integers? (parameters unknown)
    value1 = *(int*)0x00e2eff4; // global constant A
    value2 = *(int*)0x00e2b1a4; // global constant B
    if (allocatedBlock != (int*)0x0) {
        allocatedBlock[0] = value1;  // pattern: A, B, A, B, A, A, B, A
        allocatedBlock[1] = value2;
        allocatedBlock[2] = value1;
        allocatedBlock[3] = value2;
        allocatedBlock[4] = value1;
        allocatedBlock[5] = value1;
        allocatedBlock[6] = value2;
        allocatedBlock[7] = value1;
        FUN_0060cde0(); // cleanup/release after filling?
    }
    return;
}