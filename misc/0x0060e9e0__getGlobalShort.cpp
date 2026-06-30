// FUNC_NAME: getGlobalShort
// Function address: 0x0060e9e0
// Role: Returns a global 16-bit value (likely a game state flag or constant)
// The global is stored at 0x0120588c
uint16_t getGlobalShort(void)
{
    return *(uint16_t*)0x0120588c;
}