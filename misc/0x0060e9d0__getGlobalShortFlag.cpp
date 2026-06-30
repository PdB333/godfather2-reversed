// FUNC_NAME: getGlobalShortFlag
// Returns a global 16-bit value at address 0x01205760.
// Likely a game state flag or setting.

#include <cstdint>

extern uint16_t DAT_01205760;

uint16_t getGlobalShortFlag() {
    return DAT_01205760;
}