// FUNC_NAME: Player::canEnterVehicle
// Function address: 0x007bb540
// Checks if the player can enter a vehicle based on current state, settings, and vehicle availability.

bool Player::canEnterVehicle() {
    uint flags;
    char settingEnabled;
    int vehicleBase;
    int seatBase;

    // Check game settings: if setting 3 or 4 is enabled, proceed with vehicle checks
    settingEnabled = isSettingEnabled(getGameSetting(3));
    if (settingEnabled == '\0') {
        settingEnabled = isSettingEnabled(getGameSetting(4));
        if (settingEnabled == '\0') goto LAB_007bb5ac;
    }

    // Get vehicle object pointer (offset +0x74c) and compute base by subtracting 0x48
    if (*(int*)(this + 0x74c) == 0) {
        vehicleBase = 0;
    } else {
        vehicleBase = *(int*)(this + 0x74c) - 0x48; // Vehicle object base
    }

    // Get seat object pointer (offset +0x30c0) and compute base
    if (*(int*)(this + 0x30c0) == 0) {
        seatBase = 0;
    } else {
        seatBase = *(int*)(this + 0x30c0) - 0x48; // Seat object base
    }

    // If we have a vehicle and the player is not already in a vehicle (bit 10 of flags at +0x8e0)
    if ((vehicleBase != 0) && ((*(uint*)(this + 0x8e0) >> 10 & 1) == 0)) {
        // If no seat, or seat conditions are met: vehicle not in state 1 or 6, and not bit 2 of seat flags
        if ((seatBase == 0) &&
            (*(char*)(vehicleBase + 0x1a8) != '\x01') &&
            ((*(uint*)(vehicleBase + 0x1d0) >> 2 & 1) == 0) &&
            (*(char*)(vehicleBase + 0x1a8) != '\x06')) {
            return true;
        }
    } else {
        // No vehicle: check player state flags at +0x8e4 (bits 6,5,7 must be 0)
        // Also check if features 0x28 and 0x29 are disabled
        if ((seatBase == 0) &&
            (((flags = *(uint*)(this + 0x8e4), (flags >> 6 & 1) == 0) &&
              ((flags >> 5 & 1) == 0)) &&
             ((flags >> 7 & 1) == 0)) &&
            (isFeatureEnabled(0x28) == '\0') &&
            (isFeatureEnabled(0x29) == '\0')) {
            return true;
        }
    }

LAB_007bb5ac:
    // Final check: if game is not in a menu/cutscene, or player is not in a special state (byte at +0x2198)
    if ((isGameInMenuOrCutscene() == '\0') || (*(char*)(this + 0x2198) != '\0')) {
        return false;
    }
    return true;
}