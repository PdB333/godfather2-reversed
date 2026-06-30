// FUNC_NAME: setGlobalDword
// Function address: 0x0069e660
// Sets a global DWORD variable at 0x0112a070. Used during initialization (callers: 0x009267c0, 0x009272e0).
// Possible purpose: boot flag or state indicator.

// Global variable declaration (located at 0x0112a070)
int g_globalDword;

void setGlobalDword(int value)
{
    g_globalDword = value;
}