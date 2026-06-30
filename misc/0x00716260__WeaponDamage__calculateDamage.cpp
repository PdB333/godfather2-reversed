// FUNC_NAME: WeaponDamage::calculateDamage
// Address: 0x00716260
// Role: Computes final damage value with randomization, critical hit checks, and damage type scaling.
// This function reads damage base from a weapon data structure and applies modifiers based on flags.
// Uses a random number generator for damage variance.

#include <cstdint>

// Forward declarations (extern) for callee functions
extern bool isGameActive();           // 0x00800a90
extern uint32_t getDamageBase();      // 0x00701050
extern bool isCriticalHit();           // 0x00701010
extern int32_t randomInt(int32_t max); // 0x006eb670 (returns 0..max-1)

class WeaponDamage {
public:
    // Offsets:
    // +0x00: vtable?
    // +0x24: pointer to weapon data (contains damage array at +0x9c)
    // +0x154: damage flags (bit6 = some modifier? bit13 = critical immunity?)
    void* m_pWeaponData;                // +0x24
    uint32_t m_damageFlags;             // +0x154

    uint32_t calculateDamage() __fastcall;
};

uint32_t __fastcall WeaponDamage::calculateDamage() {
    if (!isGameActive()) {
        return 0;                        // Game not active, no damage
    }

    uint32_t baseDamage = getDamageBase(); // Get base damage from weapon type
                                            // (could also be index into damage array)

    // Apply damage from weapon data array if available
    if (m_pWeaponData != nullptr) {
        uint32_t* damageArray = (uint32_t*)((uint8_t*)m_pWeaponData + 0x9c);
        baseDamage = damageArray[baseDamage]; // Index into damage values
    }

    // Check critical immunity flag (bit13)
    if (m_damageFlags & (1 << 13)) {
        return baseDamage;               // Critical immune, return base
    }

    // Critical hit check
    if (isCriticalHit()) {
        // Random damage in [baseDamage/2, baseDamage]
        int32_t halfBase = baseDamage >> 1;
        int32_t range = (baseDamage - halfBase) + 1; // inclusive range count
        return halfBase + randomInt(range);
    }

    // Modifier flag (bit6) – likely for a specific damage type (e.g., explosive, melee)
    if (m_damageFlags & (1 << 6)) {
        return randomInt(3);             // Returns 0, 1, or 2
    }

    // Default: random damage in [1, baseDamage]
    return 1 + randomInt(baseDamage);
}