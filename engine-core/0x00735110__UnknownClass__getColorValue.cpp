// FUNC_NAME: UnknownClass::getColorValue
// Function at 0x00735110 - likely returns a color value (ARGB?) based on object state and pseudo-random generation.
// Seems to be part of a character/entity color system (e.g., gang colors).

#include <cstdint>

// External globals (random state)
extern uint32_t DAT_010c2678;  // Random mask
extern uint32_t DAT_012054b4;  // Random index
extern float DAT_00d5eee4;     // Multiplier
extern float DAT_010c2680[];   // Float array for pseudo-random numbers

int __fastcall getColorValue(int this) {
    int result = 0;

    // Check state at offset 0x74c: if 0 or 0x48 (72), or bit 10 at offset 0x8e0 is clear
    if ((*(int*)(this + 0x74c) == 0) ||
        (*(int*)(this + 0x74c) == 0x48) ||
        ((*(uint32_t*)(this + 0x8e0) >> 10 & 1) == 0)) {
        // Use external function to determine color mode
        int mode = FUN_00806440();
        if (mode == 2) {
            result = 0x6e185f90;
        } else if (mode == 3) {
            return 0x2504761a;
        } else {
            // Conditional return based on flag at offset 0x1f54 bit 0
            uint32_t flagMask = (uint32_t)(-(int)((*(uint8_t*)(this + 0x1f54) & 1) != 0)) & 0xf1604eff;
            return flagMask + 0xc011276a;
        }
    } else {
        // Pseudo-random color selection using global state
        uint32_t index = DAT_010c2678 & DAT_012054b4;
        DAT_012054b4 = DAT_012054b4 + 1;

        int randomVal = (int)(DAT_010c2680[index] * DAT_00d5eee4);
        if (randomVal == 0) {
            return -0x52f9a102; // 0xAD065EFE
        } else if (randomVal == 1) {
            return -0x52f9a101; // 0xAD065EFF
        } else if (randomVal == 2) {
            return -0x52f9a100; // 0xAD065F00
        }
        // else result remains 0
    }
    return result;
}