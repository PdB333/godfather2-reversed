// FUNC_NAME: DebugMenu::isCheatAllowed
// Function address: 0x007d6400
// Role: Checks whether cheat/debug menu can be activated based on button combo and game state.

#include <cstdint>

// Global configuration float; when less than this->field_0x30, cheat detection runs.
extern float g_debugMenuEnableThreshold; // _DAT_00d577a0

// Forward declarations of internal functions used by this method.
// These can be assumed to be free functions or static methods.
int __fastcall FUN_00798f50(int a); // Possibly getConfigValue or getGameStateBit
bool __fastcall FUN_0079e920(int a); // Checks some flag/condition
int __fastcall FUN_007ab330(void); // Returns non-zero if player is in-game (not paused/menu)
bool __fastcall FUN_007ab420(uint32_t buttonMask); // Returns true if button mask is currently pressed

// Member function of DebugMenu class, using __thiscall (ecx = this)
int __fastcall DebugMenu::isCheatAllowed(int thisPtr)
{
    // Check if global threshold is less than this->someFloat (0x30)
    // Typically this is a debounce timer or sensitivity setting.
    if (g_debugMenuEnableThreshold < *(float *)(thisPtr + 0x30)) {
        int configHandle = FUN_00798f50(0x37); // Likely "cheat enabled" config index
        bool cheatEnabled = FUN_0079e920(configHandle);

        if (cheatEnabled) {
            return 1; // Cheat system enabled globally
        }

        // Check a bitfield stored at this->ptr0x58 + 0x8e4
        uint32_t statusFlags = *(uint32_t *)((*(int *)(thisPtr + 0x58)) + 0x8e4);

        // Check if the high bit (sign) is set or if bit 30 is set (0x40000000)
        // These bits might indicate debugOverlayActive or similar.
        // Note: (int)uVar1 < 0 checks the sign bit (bit 31).
        if ((int)statusFlags < 0 || (statusFlags >> 0x1e & 1) != 0) {
            // Also need to be inside actual gameplay (not menus, cutscenes)
            int inGameState = FUN_007ab330();
            if (inGameState != 0) {
                // Check for specific button combos to trigger cheat/dbug menu
                bool buttonCombo1 = FUN_007ab420(8); // e.g., 8 = mask for "Select" or "Back"
                bool buttonCombo2 = FUN_007ab420(0x4000000); // e.g., large mask for "LeftBumper+RightBumper"

                if (buttonCombo1) {
                    return 1;
                }
                if (buttonCombo2) {
                    return 1;
                }
            }
        }
    }

    return 0; // Cheat not allowed
}