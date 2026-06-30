// FUNC_NAME: Entity::computeActionFlags
// Address: 0x006F1920
// Computes a bitmask of action flags based on action type and modifier bits.
// The result always includes bit 3 (0x8) as a valid flag.
// Checks this+0x50 bit 4 (0x4) to switch between two base flag sets.

uint __thiscall Entity::computeActionFlags(uint actionId, byte modifierFlags) {
    uint flags;

    // Check bit 4 of field at +0x50: possibly "useAltFlagSet"?
    if ((*(byte *)(this + 0x50) & 0x4) == 0) {
        // Normal flag set based on action type
        switch (actionId) {
        case 6:
            flags = 0x1000000;  // Bit 24
            break;
        case 7:
            flags = 0x40000;    // Bit 18
            break;
        case 8:
            flags = 0x20000;    // Bit 17
            break;
        case 9:
            flags = 0x200000;   // Bit 21
            break;
        default:
            flags = 0x100000;   // Bit 20
        }
    } else {
        // Alternative base flag set
        flags = 0x400010;       // Bits 22, 5, 4
    }

    // Apply modifier flags from param_3 (byte)
    if ((modifierFlags & 0x8) != 0) {
        flags |= 0x20;          // Set bit 5
    }
    if ((modifierFlags & 0x10) != 0) {
        if ((modifierFlags & 0x20) != 0) {
            return flags | 0x48; // Bits 3 and 6 (since 0x48 = 0x40 | 0x08)
        }
        if ((modifierFlags & 0x40) != 0) {
            flags |= 0x80;      // Set bit 7
        }
    }

    // Always add the "valid" flag (bit 3)
    return flags | 0x8;
}