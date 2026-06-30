// FUNC_NAME: setGlobalFlagValue
// Address: 0x0042c1a0
// Sets a global flag/value (DAT_0110ac30), likely used by the engine for state control.
void setGlobalFlagValue(uint32_t newValue) {
    g_globalFlag = newValue; // DAT_0110ac30
}