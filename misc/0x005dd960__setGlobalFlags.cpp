// FUNC_NAME: setGlobalFlags
void setGlobalFlags(uint flag1, uint flag2, uint flag3)
{
    // Global variables at addresses: 0x00f15b78, 0x00f15b7c, 0x012056c0, 0x00f15b80
    gFlag1 = flag1;        // +0x00f15b78
    gFlag2 = flag2;        // +0x00f15b7c
    gFlag3 = flag3;        // +0x012056c0
    gFlagOR = flag1 | flag2 | flag3; // +0x00f15b80
}