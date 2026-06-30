// FUN_004704d0: MovementController::setSteeringInput

struct MovementController {
    // ... other members ...
    float currentSpeed;                     // +0x150
    float computedRate;                     // +0x154
    unsigned short flags;                   // +0x15e
    // ... more ...
};

void __thiscall MovementController::setSteeringInput(int speed, bool forward, bool backward) {
    // Set flag bit 2 (0x4) if forward movement requested
    if (forward) {
        flags |= 0x4;
    }
    // Set flag bit 3 (0x8) if backward movement requested
    if (backward) {
        flags |= 0x8;
    }
    if (speed != 0) {
        float fSpeed = static_cast<float>(speed);
        if (speed < 0) {
            // Convert negative integer to positive float by adding a large constant
            // (likely to handle unsigned representation or wrap‑around)
            fSpeed += DAT_00e44578; // constant at 0x00e44578
        }
        // Compute and store a rate (e.g., time factor, acceleration, etc.)
        computedRate = DAT_00e2eff4 / fSpeed; // constant at 0x00e2eff4
        return;
    }
    // If speed is zero but currentSpeed is non‑zero, reset it and set idle flag
    if (currentSpeed != 0.0f) {
        currentSpeed = 0.0f;
        flags |= 0x100; // Idle flag (bit 8)
    }
    // Call additional stop logic (likely a separate function)
    FUN_004705e0();
}