// FUNC_NAME: TableResolver::resolve
void __thiscall TableResolver::resolve(int category, int arg1, int arg2)
{
    // Global state variables (likely part of a static table manager)
    g_currentCategory = category;   // DAT_0112537c
    g_currentArg1 = arg2;           // DAT_01125380
    g_currentArg2 = arg1;           // DAT_01125384

    uint index1; // DAT_01125388 (byte)
    uint index2; // DAT_01125389 (byte)

    if (category == 3)
    {
        index1 = 0;
        index2 = 0x12; // 18
    }
    else if (category == 4)
    {
        index1 = 2;
        index2 = 0x13; // 19
    }
    else if (category == 5)
    {
        index1 = 2;
        index2 = 0x14; // 20
    }
    else if (category == 6)
    {
        index1 = 2;
        index2 = 0x15; // 21
    }
    else
    {
        // Default: index1 is based on whether arg2 == 1
        index1 = (arg2 == 1) ? 1 : 0;
        // index2 = (arg1 != 1) ? ((arg1 != 1) - 1) & 9 : 0? Actually computed as:
        // ((arg1 != 1) - 1U & 9) + category * 3 + arg2
        index2 = ((arg1 != 1) - 1U) & 9; // mask to 0..9
        index2 += category * 3 + arg2;
    }

    g_tableIndex1 = index1; // DAT_01125388
    g_tableIndex2 = index2; // DAT_01125389

    // Look up results from two global arrays
    g_result1 = g_tableArray1[index1];         // DAT_0112538c is an array of bytes? (size per element unknown)
    g_result2 = *(int*)((int)&g_tableArray2 + index2 * 4); // DAT_01125398 is an array of 4-byte values

    // g_result1 -> DAT_011252e8
    // g_result2 -> DAT_011252ec
}