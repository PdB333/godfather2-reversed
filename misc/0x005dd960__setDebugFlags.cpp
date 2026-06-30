// FUNC_NAME: setDebugFlags
void setDebugFlags(uint flag0, uint flag1, uint flag2)
{
    // Global debug flag storage
    // DAT_00f15b78 = flag0
    g_debugFlag0 = flag0;
    // DAT_00f15b7c = flag1
    g_debugFlag1 = flag1;
    // DAT_012056c0 = flag2
    g_debugFlag2 = flag2;
    // DAT_00f15b80 = OR of all three flags (combined mask)
    g_debugFlagCombined = flag0 | flag1 | flag2;
}