// FUNC_NAME: PlayerFlagsManager::hasFlag
// Function at 0x007f7e90 - checks if a specific flag is set in a 32-bit bitfield at offset 0x604
// param_2: flag index (0-9) or 0xFF to check if any flag is set
bool __thiscall PlayerFlagsManager::hasFlag(uint32_t* this, uint8_t flagIndex)
{
    bool result = false;
    // Only check if flagIndex is 0-9 (because (flagIndex+1) < 0xB) or the special 0xFF
    if ((uint8_t)(flagIndex + 1) < 0xB) {
        if (flagIndex == 0xFF) {
            // Special case: return true if any flag is set (whole int non-zero)
            return *(int*)((uint8_t*)this + 0x604) != 0;
        }
        // Check the specific bit, using 5-bit mask for safety (flagIndex & 0x1F)
        result = (*(uint32_t*)((uint8_t*)this + 0x604) & (1 << (flagIndex & 0x1F))) != 0;
    }
    return result;
}