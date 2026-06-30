// FUNC_NAME: setGlobalFlag
// Function at 0x0060b610: Writes a byte/boolean value to a global flag.
void setGlobalFlag(bool value)
{
    // Global variable at 0x00f15a3a
    g_bGlobalFlag = value;
}