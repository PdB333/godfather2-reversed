// FUNC_NAME: Player::canExitVehicle
// Function address: 0x007d79f0
// Description: Checks if the player can exit a vehicle. Requires that the player is not pressing certain action buttons (0xc or 0xd) and that vehicle state conditions are met.

bool __thiscall Player::canExitVehicle(char actionType) {
    // Get global input/game state manager
    int* inputManager = getInputManager();
    if (!(*(byte*)(inputManager + 4) & 0x20)) {
        return false;
    }

    // Get player state manager (e.g., player mode flags)
    int* playerState = getPlayerStateManager();
    if ((*(byte*)(playerState + 4) & 2) != 0) {
        int* vehicle = *(int**)(this + 0x58); // +0x58: pointer to current vehicle
        bool isActionPressed;
        if (actionType == 0) {
            int binding = getActionBinding(0xd); // action 0xd (e.g., accelerate)
            isActionPressed = isActionHeld(binding);
        }
        else {
            int binding = getActionBinding(0xc); // action 0xc (e.g., brake)
            isActionPressed = isActionHeldAlt(binding);
        }

        // Determine if exit is allowed based on vehicle state
        bool exitAllowed = true;
        if (!isActionPressed) {
            exitAllowed = false;
        }
        else if ((*(uint*)(vehicle + 0x8e0) >> 10 & 1) != 0 &&
                 (int* vehiclePhysics = getVehiclePhysics(), (*(uint*)(vehiclePhysics + 0x1d0) >> 3 & 1) == 0)) {
            exitAllowed = false;
        }
        else if (*(int*)(vehicle + 0x30c0) != 0 && *(int*)(vehicle + 0x30c0) != 0x48) {
            exitAllowed = false;
        }

        // Check global UI/pause condition
        bool isUIActive = isUIActive();
        return exitAllowed && !isUIActive && !isActionPressed;
    }
    return false;
}