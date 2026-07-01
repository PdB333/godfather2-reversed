// FUNC_NAME: WeaponData::getDamageForLevel
// Function address: 0x00916c70
// Maps a weapon type (stored at +0xB8) and an attack level (0=light, 1=medium, 2=heavy) to a damage value.
// Called in many places for damage calculation.

enum WeaponType : int {
    WEAPON_TYPE_UNKNOWN_10 = 10,
    WEAPON_TYPE_UNKNOWN_11 = 11,
    WEAPON_TYPE_UNKNOWN_12 = 12,
    WEAPON_TYPE_UNKNOWN_13 = 13,
    WEAPON_TYPE_UNKNOWN_14 = 14,
    WEAPON_TYPE_UNKNOWN_15 = 15,
    WEAPON_TYPE_UNKNOWN_16 = 16,
    WEAPON_TYPE_UNKNOWN_18 = 0x12,
    WEAPON_TYPE_UNKNOWN_19 = 0x13,
    WEAPON_TYPE_UNKNOWN_20 = 0x14,
    WEAPON_TYPE_UNKNOWN_21 = 0x15,
    WEAPON_TYPE_UNKNOWN_22 = 0x16,
    WEAPON_TYPE_UNKNOWN_23 = 0x17,
    WEAPON_TYPE_UNKNOWN_24 = 0x18,
    WEAPON_TYPE_UNKNOWN_25 = 0x19
};

enum AttackLevel : int {
    ATTACK_LIGHT = 0,
    ATTACK_MEDIUM = 1,
    ATTACK_HEAVY = 2
};

// Damage values returned
const int DAMAGE_NONE = 0;
const int DAMAGE_LIGHT_PUNCH = 8;
const int DAMAGE_MEDIUM_PUNCH = 1;
const int DAMAGE_HEAVY_PUNCH = 9;
// ... etc.

int __thiscall WeaponData::getDamageForLevel(AttackLevel attackLevel) {
    WeaponType weaponType = *(WeaponType*)(this + 0xB8); // weapon type ID at offset 0xB8
    
    int damage = 0;
    
    switch (weaponType) {
        case WEAPON_TYPE_UNKNOWN_10:
        case WEAPON_TYPE_UNKNOWN_11:
        case WEAPON_TYPE_UNKNOWN_12:
            switch (attackLevel) {
                case ATTACK_LIGHT:
                    return 0;
                case ATTACK_MEDIUM:
                    return 0x1f; // 31
                case ATTACK_HEAVY:
                    return 0x1d; // 29
                // Note: case 12 returns 0x1e (30) for heavy? The grouping is odd, but the code only has case 0,1,2 for all three weapon types.
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_13:
            if (attackLevel == ATTACK_LIGHT) {
                return 0x23; // 35
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x21; // 33
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x22; // 34
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_14:
            if (attackLevel == ATTACK_LIGHT) {
                return 0x26; // 38
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x24; // 36
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x25; // 37
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_15:
            if (attackLevel == ATTACK_LIGHT) {
                return 0x29; // 41
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x27; // 39
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x28; // 40
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_16:
            if (attackLevel == ATTACK_LIGHT) {
                return 0x2c; // 44
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x2a; // 42
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x2b; // 43
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_18: // 0x12
            if (attackLevel == ATTACK_LIGHT) {
                return 0x1b; // 27
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x1c; // 28
            }
            // No heavy for this weapon type
            break;
            
        case WEAPON_TYPE_UNKNOWN_19: // 0x13
            if (attackLevel == ATTACK_LIGHT) {
                return 0x15; // 21
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x0e; // 14
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x12; // 18
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_20: // 0x14
            return 0x0c; // 12 (all levels same? Possibly only light?)
            
        case WEAPON_TYPE_UNKNOWN_21: // 0x15
            return 0x0b; // 11
            
        case WEAPON_TYPE_UNKNOWN_22: // 0x16
            if (attackLevel == ATTACK_LIGHT) {
                return 0x16; // 22
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 0x0d; // 13
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x14; // 20
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_23: // 0x17
            if (attackLevel == ATTACK_LIGHT) {
                return 0x17; // 23
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 10;
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 0x10; // 16
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_24: // 0x18
            if (attackLevel == ATTACK_LIGHT) {
                damage = 0x18; // 24
            } else if (attackLevel == ATTACK_MEDIUM) {
                return 0x0f; // 15
            } else if (attackLevel == ATTACK_HEAVY) {
                return 0x13; // 19
            }
            break;
            
        case WEAPON_TYPE_UNKNOWN_25: // 0x19
            if (attackLevel == ATTACK_LIGHT) {
                return 8; // light punch?
            }
            if (attackLevel == ATTACK_MEDIUM) {
                return 1; // medium punch?
            }
            if (attackLevel == ATTACK_HEAVY) {
                return 9; // heavy punch?
            }
            break;
    }
    
    return damage; // default return 0 if no case matched (or if case 0x18 with light attack)
}