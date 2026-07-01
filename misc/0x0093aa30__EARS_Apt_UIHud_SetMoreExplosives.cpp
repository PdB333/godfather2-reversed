// Xbox PDB: EARS_Apt_UIHud_SetMoreExplosives
// FUNC_NAME: PlayerActionableInfo::setShowMoreExplosives

// Address: 0x0093aa30
// Role: Controls the visibility of the "More Explosives" option in the action wheel UI.
// The function sets a flag at +0x5c (bit 26) based on the input boolean, and then conditionally shows/hides
// the explosive UI via a Lua callback.

void __thiscall PlayerActionableInfo::setShowMoreExplosives(int thisPtr, char showMore)
{
    uint flags = *(uint *)(thisPtr + 0x5c); // +0x5c: bitfield of UI/action flags

    if (showMore == '\0') {
        // Clear bit 26 (0x04000000) – hide explosives option
        flags &= 0xfbffffff;
    } else {
        // Set bit 26 – show explosives option
        flags |= 0x04000000;
    }
    *(uint *)(thisPtr + 0x5c) = flags;

    // Check if we are allowed to actually display the UI element
    // +0x48: some state flag (e.g., isInActionMode, hasItemSelected)
    // +0x49: additional flags, bits 1 and 3 (0x0A) must be clear to proceed
    if ((*(char *)(thisPtr + 0x48) != '\0') && ((*(char *)(thisPtr + 0x49) & 0x0A) == 0)) {
        if ((showMore != '\0') && ((*(uint *)(thisPtr + 0x5c) >> 0x1c & 1) != 0)) {
            // Bit 28 is also set – trigger Lua event to show the extra explosives
            // (e.g., when player has multiple explosive types)
            FUN_005a04a0("ShowMoreExplosives", 0, &DAT_00d8a64c, 0);
            return;
        }
        // Otherwise, hide the additional explosives option
        FUN_005a04a0("HideMoreExplosives", 0, &DAT_00d8a64c, 0);
    }
}