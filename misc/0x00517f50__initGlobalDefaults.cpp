// FUNC_NAME: initGlobalDefaults

void initGlobalDefaults(void)
{
    // Initialize global state variables to default values.
    // Constants are global read-only values set elsewhere.
    g_globalVar0x20 = kConstantA;          // offset 0x20: first field set to constant A
    g_globalVar0x24 = kConstantA;          // offset 0x24: second field set to constant A
    g_globalVar0x10 = 0;                   // offset 0x10: clear to zero
    g_globalVar0x14 = 0;                   // offset 0x14: clear to zero
    g_globalVar0x18 = 0;                   // offset 0x18: clear to zero
    g_globalVar0x1C = kConstantB;          // offset 0x1C: set to constant B
    g_globalVar0x00 = kConstantB;          // offset 0x00: set to constant B
    g_globalVar0x04 = kConstantB;          // offset 0x04: set to constant B
    g_globalVar0x08 = kConstantB;          // offset 0x08: set to constant B
    g_globalVar0x28 = kConstantC;          // offset 0x28: set to constant C
    g_globalVar0x2C = 0;                   // offset 0x2C: clear to zero
    g_globalVar0x40 = 0;                   // offset 0x40: clear to zero
    g_globalVar0x44 = 0;                   // offset 0x44: clear to zero
    g_globalVar0x30 = 0;                   // offset 0x30: clear to zero
    g_globalVar0x34 = 0;                   // offset 0x34: clear to zero
    g_globalVar0x38 = kConstantB;          // offset 0x38: set to constant B
    g_globalVar0x3C = kConstantB;          // offset 0x3C: set to constant B
    g_globalVar0x0C = 0;                   // offset 0x0C: clear to zero
    g_globalVar0x50 = 0;                   // offset 0x50: clear to zero
    g_globalVar0x8C = 0;                   // offset 0x8C: clear to zero
}