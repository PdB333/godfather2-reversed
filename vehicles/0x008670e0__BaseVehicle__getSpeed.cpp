// FUNC_NAME: BaseVehicle::getSpeed
void __thiscall BaseVehicle::getSpeed(float *outSpeed, float *outDirection) {
    float *speedPtr = outSpeed;
    float speedValue;

    if (outDirection != nullptr) {
        // Convert signed timer from offset 0xfd4 to float speed
        speedValue = (float)(*(uint *)(this + 0xfd4) & 0x7fffffff) * 0.025f; // DAT_00d75750 = 0.025? (example)
        *outDirection = speedValue;
        if (*(int *)(this + 0xfd4) < 0) {
            *outDirection = speedValue + 0.0f; // DAT_00d75758 likely 0.0
        }
    }

    if (outSpeed != nullptr) {
        // Check if the vehicle is in a certain state (e.g., on ground)
        int stateCheck = FUN_006019b0(2, 1); // Arguments: e.g., kCheckType_Ground, kCheckFlag_Moving
        if (stateCheck != 0) {
            int speedInt = FUN_00865880(2, 1, this + 0x1050); // Get speed from a substructure
            float speedFloat = (float)speedInt;
            if (speedInt < 0) {
                speedFloat = speedFloat + 0.0f; // DAT_00e44578 likely 0.0
            }
            *speedPtr = speedFloat * 0.025f; // DAT_00d75750
        } else {
            *speedPtr = 0.0f; // DAT_00d5eee4 likely 0.0
        }
    }
}