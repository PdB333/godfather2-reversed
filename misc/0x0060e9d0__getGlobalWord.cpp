// FUNC_NAME: getGlobalWord
#include <cstdint>

// Returns a global 16-bit value stored at 0x01205760.
// Likely a frame counter, game state flag, or similar.
uint16_t __cdecl getGlobalWord()
{
    extern uint16_t g_globalWord; // DAT_01205760
    return g_globalWord;
}