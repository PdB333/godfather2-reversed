// FUNC_NAME: BuildingUIManager::updateIconSelectionState
void __thiscall BuildingUIManager::updateIconSelectionState(int thisPtr, int iconType) {
    // Based on iconType, set internal state at +0x5c to a specific value
    if (iconType == 7) {
        *(int *)(thisPtr + 0x5c) = 8;
    }
    else if (iconType == 8) {
        *(int *)(thisPtr + 0x5c) = 6;
    }
    else if (iconType == 9) {
        *(int *)(thisPtr + 0x5c) = 7;
    }

    // Notify the icon system that selection changed (likely a debug/logging call)
    FUN_005a04a0("UpdateIconSelected", 0, &DAT_00d87b2c, 0); // DAT_00d87b2c: "Icon" or similar string

    // Local stack variable initialization
    int local_c = DAT_011301f0; // some global pointer or structure
    int local_8 = 0;
    char local_4 = 0; // unused? or part of a struct

    // Call to update or refresh icon info (maybe set data for the selected icon)
    FUN_00408a00(&local_c, 0);

    // Notify the icon system that info changed
    FUN_005a04a0("UpdateIconInfo", 0, &DAT_00d87b2c, 0);

    // Set dirty flag (bit 2) in flags at +0x50 to trigger a redraw
    *(unsigned int *)(thisPtr + 0x50) |= 4;
}