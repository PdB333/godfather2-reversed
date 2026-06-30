// FUNC_NAME: Player::canPerformAction
// Address: 0x007181c0
// Role: Determines if the player can perform a specific action (likely interact with vehicle) based on vehicle state, game mode, and player state flags.

bool __fastcall Player::canPerformAction(void)
{
    // Check vehicle-pointer offset 0x330 (likely a member pointer to a vehicle or component)
    int* vehicleData = *(int**)(this + 0x330);
    int vehicleBase = 0;
    if (vehicleData != nullptr) {
        // Subtract 0x48 to get the parent object (e.g., from a member offset within a larger vehicle structure)
        vehicleBase = (int)vehicleData - 0x48;
    }

    // Get some state from vehicleBase (likely the vehicle's current state/phase)
    int vehicleState = 0;
    if (vehicleBase != 0) {
        vehicleState = FUN_0071ce70(vehicleBase);  // GetVehicleState or similar
    }

    // Check another vehicle-related offset 0x338
    int* vehicleFlags = *(int**)(this + 0x338);
    if (vehicleFlags == nullptr) {
        return false;  // Null means no action allowed
    }
    if (vehicleFlags == (int*)0x48) {
        return false;  // Special sentinel value (0x48) also prevents action
    }

    // Get global game manager (FUN_007ff880 likely returns SimManager or NetSession)
    void* simManager = (void*)FUN_007ff880();
    bool isGameModeValid = false;
    if (simManager == nullptr || *(int*)((int)simManager + 0xb74) == 0) {
        // No sim manager or online mode flag not set
        // Also check single-player mode and debug flags
        if (FUN_007f7c60() == '\0' || FUN_00716d40() != '\0') {
            isGameModeValid = true;
        }
    }
    // Note: the original logic is inverted: bVar1 = true if (no simManager OR offset0xb74==0) AND (singleplayer flag false OR debug flag true)

    // Check player's own bitfield at offset 0x18 -> +0x1f54 bit 2
    uint bits = *(uint*)(*(int*)(this + 0x18) + 0x1f54);
    if ((bits >> 2 & 1) != 0) {
        return false;
    }

    // Check vehicle state (if available)
    if (vehicleState == 0) {
        return false;
    }

    // Check vehicle's internal state at offset 0x38 (likely an enum: 0=idle, 3=entering, 4=exiting)
    int vehicleInternalState = *(int*)(vehicleState + 0x38);
    if (vehicleInternalState != 3 && vehicleInternalState != 4 && vehicleInternalState != 0) {
        return false;
    }

    // Finally, check single-player state again (condensed from bVar1 and last check)
    if (!isGameModeValid) {
        return false;
    }
    char isSinglePlayer = FUN_007f7c60();
    if (isSinglePlayer != '\0') {
        return false;
    }

    // All conditions passed
    return true;
}