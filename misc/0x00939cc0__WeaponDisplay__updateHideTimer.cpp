// FUNC_NAME: WeaponDisplay::updateHideTimer
// Address: 0x00939cc0
// Role: Updates a hide weapon display timer. When timer exceeds 1500ms, sends a "HideWeaponDisplay" message and clears the flag.

// Assuming these globals are defined elsewhere
extern int gFrameTime; // DAT_01206804
extern void BroadcastMessage(const char* message, int param, const char* extra, int flag); // FUN_005a04a0

// WeaponDisplay class (partial)
class WeaponDisplay {
public:
    uint32_t m_nFlags; // +0x5C
    int m_nHideTimer; // +0xE8

    enum Flags {
        kFlagHideTimerActive = 1 << 7 // bit 7
    };

    // Returns 1 if hide occurred, 0 if still counting
    int __fastcall updateHideTimer(); // actual calling convention is __thiscall via ECX
};

int __fastcall WeaponDisplay::updateHideTimer()
{
    // Check if the hide timer is active
    if ((m_nFlags >> 7 & 1) != 0) {
        // Accumulate frame time
        m_nHideTimer += gFrameTime;

        // If still below 1500ms (0x5DC), do nothing
        if (m_nHideTimer < 1500) {
            return 0;
        }

        // Time expired: issue hide weapon message
        BroadcastMessage("HideWeaponDisplay", 0, &DAT_00d8a64c, 0);

        // Clear the hide timer active flag (bit 7) and also bits 0x180000C0? Mask: 0xe7ffff3f
        m_nFlags &= 0xe7ffff3f; // clears bit 7 and some others
    }
    return 1;
}