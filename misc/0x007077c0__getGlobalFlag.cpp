// FUNC_NAME: getGlobalFlag
// Address: 0x007077c0
// Role: Returns the value of a global DWORD at 0x00e516f8.
// This is likely a simple accessor for a game state flag or configuration variable.
uint32_t getGlobalFlag() {
    return DAT_00e516f8;  // Global DWORD at 0x00e516f8
}