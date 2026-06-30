// FUNC_NAME: applyDamageModifier
// Address: 0x0060c9d0
// Applies a damage reduction or health modifier based on the modifierType.
// Used in several damage-related functions (e.g., FUN_0060cde0, FUN_0060cae0, etc.)
// The modifierType values likely correspond to difficulty or damage source types.
uint __fastcall applyDamageModifier(uint damage, uint modifierType)
{
    switch (modifierType) {
    case 2:
        return damage >> 1;          // Half damage
    case 3:
        return damage - 1;           // Subtract 1
    case 4:
        return damage / 3;           // Divide by 3
    case 5:
    case 6:
        damage = damage - 2;         // Subtract 2
        break;
    case 0xD:                        // 13
        return damage >> 2;          // Quarter damage
    }
    return damage;
}