// Function address: 0x004103b0
// Role: Input button state filter/mask check for a specific controller slot.
// This function checks whether a set of buttons (param_3) matches certain conditions
// based on per-slot masks stored in a controller state array.
// The controller state array is at this+0x2c, each entry 0x44 bytes.
// Offsets within each entry:
//   +0x10: ushort mask1 (likely "allowed" buttons)
//   +0x12: ushort mask2 (likely "blocked" or "modifier" buttons)
//   +0x14: ushort mask3 (buttons to clear/ignore)
//   +0x3e: char  active flag (non-zero if the slot is in use)
//
// Parameters:
//   slotIndex - controller slot index (0-15). The value 0x12 (18) is rejected.
//   buttonFlags - ushort representing current button state bits.
//   mode - one of 4 comparison modes:
//      0: returns true if (buttonFlags & ~mask1) == buttonFlags  (no extra buttons beyond mask1)
//      1: returns true if (buttonFlags & mask1) == buttonFlags  (all buttons are in mask1)
//      2: returns true if (buttonFlags & (mask1 & ~mask2)) == buttonFlags
//      3: returns true if (buttonFlags & (~mask1 & mask2)) == buttonFlags
// Return: Upper byte is the upper byte of buttonFlags (preserved), lower byte is boolean result.

uint __thiscall CheckButtonState(int thisPtr, byte slotIndex, ushort buttonFlags, byte mode)
{
    uint result;
    int entryBase;
    ushort mask1, mask2, mask3;
    bool conditionMet;

    // Default result: preserve upper byte from buttonFlags, lower byte zero
    result = ((uint)buttonFlags >> 8) << 8;

    // Reject slot index 0x12 (18) and require slot index < 16 and slot active
    if ((slotIndex != 0x12) && (slotIndex < 0x10) &&
        (*(char*)(thisPtr + 0x6a + slotIndex * 0x44) != '\0'))
    {
        entryBase = thisPtr + 0x2c + slotIndex * 0x44;
        mask1 = *(ushort*)(entryBase + 0x10);
        mask2 = *(ushort*)(entryBase + 0x12);
        mask3 = *(ushort*)(entryBase + 0x14);

        // Clear any bits that are set in mask3 (ignore them)
        buttonFlags = buttonFlags & ~mask3;

        // Mode selection
        switch (mode)
        {
        case 0:
            // Check: (buttonFlags & ~mask1) == buttonFlags
            // i.e., all set buttons are within mask1 (no extras)
            conditionMet = ((~mask1 & buttonFlags) == buttonFlags);
            break;

        case 1:
            // Check: (buttonFlags & mask1) == buttonFlags
            // i.e., all set buttons are present in mask1 (subset)
            conditionMet = ((mask1 & buttonFlags) == buttonFlags);
            break;

        case 2:
            // Check: (buttonFlags & (mask1 & ~mask2)) == buttonFlags
            // i.e., all set buttons are in mask1 but not in mask2
            conditionMet = ((mask1 & ~mask2 & buttonFlags) == buttonFlags);
            break;

        case 3:
            // Check: (buttonFlags & (~mask1 & mask2)) == buttonFlags
            // i.e., all set buttons are not in mask1 but in mask2
            conditionMet = ((~mask1 & mask2 & buttonFlags) == buttonFlags);
            break;

        default:
            conditionMet = false;
            break;
        }

        // Combine upper byte of buttonFlags with boolean condition
        result = ((uint)(buttonFlags >> 8) << 8) | (uint)conditionMet;
    }

    return result;
}