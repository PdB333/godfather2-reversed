// Xbox PDB: EARS_Apt_UIHud_UpdateWeaponName
// FUNC_NAME: HUDManager::updateWeaponName
// Address: 0x00939c50
// This function updates the weapon name displayed on the HUD. It clears the buffer,
// then if a weapon data pointer is provided, it copies the weapon name from that data.
// The debug log "UpdateWeaponName" is printed if a debug flag is set.

#include <cstring>   // for memset
#include <cstdint>

// Forward declarations of external functions (assumed from game codebase)
extern void GameStringCopy(void* dest, size_t maxChars, const void* format, const void* source); // FUN_005c4630
extern void DebugPrint(const char* tag, int unknown1, const void* channel, int unknown2);       // FUN_005a04a0

// External symbol references (addresses known from data refs)
extern const void* PTR_LAB_00d78708; // Format string or localization key for weapon name
extern const void* DAT_00d8a64c;     // Debug channel identifier

class HUDManager {
public:
    // Size 0xE4+? Unknown full class size, only relevant offsets shown
    // +0x5C: Bitfield of debug flags (bit 6 indicates weapon name logging enabled)
    uint32_t m_debugFlags; 
    // +0xE0: Pointer to a wide-character buffer for the weapon name (0x80 bytes = 64 wchar_t)
    wchar_t* m_weaponNameBuffer; // Actually a pointer to a buffer, allocation elsewhere

    // Method to update the weapon name
    void updateWeaponName(void* pWeaponData) {
        // Clear the weapon name buffer (set to zero)
        memset(m_weaponNameBuffer, 0, 0x80);

        // If valid weapon data is provided, copy the weapon name from its structure
        if (pWeaponData != nullptr) {
            // pWeaponData + 0x1C8 is assumed to be a pointer to the weapon name string
            // (likely a wide-character string, possibly localized)
            void* pWeaponName = *(void**)((uint8_t*)pWeaponData + 0x1C8); // +0x1C8: weapon name pointer
            GameStringCopy(m_weaponNameBuffer, 0x80, PTR_LAB_00d78708, pWeaponName);
        }

        // Debug logging: if flag bit 6 is set, log the update event
        if ((m_debugFlags >> 6) & 1) {
            DebugPrint("UpdateWeaponName", 0, DAT_00d8a64c, 0);
        }
    }
};
```