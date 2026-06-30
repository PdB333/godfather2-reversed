// FUNC_NAME: GameSettings::isDebugFeatureEnabled

#include <cstdint>

// Function at 0x0071f2c0
// Checks whether a debug feature (specified by hash in param_1+0x24) is enabled,
// and returns a modified pointer with low byte set to 1 if conditions are met.
// param_1: Pointer to a GameSettings object (likely a singleton)
// Returns: 0 or a pointer value with low byte = 1 indicating the feature is active.
uint32_t __fastcall GameSettings::isDebugFeatureEnabled(int param_1)
{
    char cVar1;
    uint32_t uVar2 = 0;          // Default return value (low byte cleared)
    int iVar3;

    // Read a handle/ID at offset +0x04
    int handle = *(int*)(param_1 + 0x04);
    if (handle != 0 && handle != 0x48) {
        // Convert handle to an object pointer by subtracting 0x48
        if (handle == 0) {
            iVar3 = 0;
        } else {
            iVar3 = handle - 0x48;
        }

        // Check bit 25 (0x19) at offset 0x1F58 in the object
        if ((*(uint32_t*)(iVar3 + 0x1F58) >> 0x19 & 1) == 0) {
            // Call an internal function; returns 0 when debug is allowed
            uVar2 = FUN_007f47a0();
            if ((char)uVar2 == '\0') {
                // Check several debug/cheat flags by hash ID
                bool flag1 = (FUN_0045eec0(0x2ca3cff6) != 0); // e.g., "enableDebugMenu"
                bool flag2 = (FUN_0045eec0(0x6c6aed11) != 0); // e.g., "enableCheats"
                bool flag3 = (FUN_0045eec0(0x3598f590) != 0); // e.g., "godMode"

                // Check a hash from param_1+0x24 (possibly a custom cheat code)
                uint32_t customHash = *(uint32_t*)(param_1 + 0x24);
                bool flag4 = (FUN_0045eec0(customHash) != 0);

                if (flag1 || flag2 || flag3 || flag4) {
                    // Re-compute the object pointer (handle - 0x48)
                    if (handle == 0) {
                        uVar2 = 0;
                    } else {
                        uVar2 = handle - 0x48;
                    }

                    // Check a byte at offset 0x1B8C in the object
                    if (*(char*)(uVar2 + 0x1B8C) == '\0') {
                        // Return object pointer with low byte forced to 1 (flag set)
                        // Equivalent to: (uVar2 & 0xFFFFFF00) | 1
                        return (uVar2 & 0xFFFFFF00) | 1;
                    }
                }
            }
            uVar2 = 0;  // Fallback: clear low byte
        }
    }
    return uVar2;
}