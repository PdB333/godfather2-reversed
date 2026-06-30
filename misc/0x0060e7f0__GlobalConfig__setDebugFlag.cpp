// FUNC_NAME: GlobalConfig::setDebugFlag
// Function at 0x0060e7f0 - Sets a global debug/config flag (stored at 0x012058b4)
void setDebugFlag(int value)
{
    g_debugFlag = value; // 0x012058b4: debug/config flag
}