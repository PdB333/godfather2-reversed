// FUNC_NAME: adjustDamageValue
// Function address: 0x0060c9d0
// Role: Applies a damage modifier based on a type ID (likely damage type or armor type).
// Modifiers: 2 -> halve (>>1), 3 -> subtract 1, 4 -> divide by 3, 5/6 -> subtract 2, 13 -> quarter (>>2)

uint __fastcall adjustDamageValue(uint baseValue, int modifierType)
{
    switch(modifierType)
    {
        case 2:                     // Halve damage
            return baseValue >> 1;
        case 3:                     // Reduce by 1
            return baseValue - 1;
        case 4:                     // Reduce to one third
            return baseValue / 3;
        case 5:
        case 6:                     // Reduce by 2
            baseValue = baseValue - 2;
            break;
        case 13:                    // Quarter damage
            return baseValue >> 2;
        // Default: no change
    }
    return baseValue;
}