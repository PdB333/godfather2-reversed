// FUNC_NAME: getGlobalFlag
unsigned char getGlobalFlag(void)
{
    // Returns the value of a global byte flag at 0x00f15a39
    extern unsigned char g_globalFlag;
    return g_globalFlag;
}