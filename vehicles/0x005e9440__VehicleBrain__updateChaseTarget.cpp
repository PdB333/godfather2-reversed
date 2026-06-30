// FUNC_NAME: VehicleBrain::updateChaseTarget
// Address: 0x005e9440
// Updates chase target position and state for vehicle AI.
// Uses target structure (EDI) with float speed at +0x4 and bool at +0xc.
// Global DAT_00e2e230 is likely a speed multiplier (e.g., chaseSpeedFactor).
// Global DAT_01223518 is a pointer to some game time or frame counter (int at +8).

struct ChaseTarget {
    float speed;      // +0x4
    char unknown0C;   // +0xC (bool flag)
};

// Global constants
extern float chaseSpeedFactor; // DAT_00e2e230
extern int* gameTimePtr;       // DAT_01223518 (points to int at +8)

void __thiscall VehicleBrain::updateChaseTarget(ChaseTarget* target) {
    float speed = target->speed;
    FUN_005dbc10((double)speed); // Possibly a debug/log call

    int state = *(int*)(this + 0x484); // Current state (1=idle,2=drive,3=chase,4=?)

    if (state == 4 || state == 1 || state == 2 || state == 3) {
        int newTarget = (int)(speed * chaseSpeedFactor);
        int gameTime = *(int*)(gameTimePtr + 8); // +8 offset

        // Condition: if not in state 3, or if newTarget is less than (currentTarget - gameTime + someOffset)
        if (state != 3 || newTarget < (*(int*)(this + 0x1B8) - gameTime) + *(int*)(this + 0x204)) {
            *(int*)(this + 0x204) = gameTime;
            *(int*)(this + 0x1B8) = newTarget;
        }

        *(int*)(this + 0x1DC) = *(int*)(this + 0x1D8); // Copy previous target
        *(int*)(this + 0x1BC) = 0;                     // Reset counter
        *(char*)(this + 0x285) = 0;                    // Clear flag
        *(char*)(this + 0x286) = 0;                    // Clear flag

        if (state != 3) {
            *(int*)(this + 0x484) = 3; // Set state to chase
            char result = FUN_005e8900(); // Notify state change
            if (result != 0) {
                *(int*)(this + 0x480) = *(int*)(this + 0x484); // Save previous state
            }
        }

        if (*(char*)(target + 0xC) != 0) {
            *(int*)(this + 0x210) = 0; // Reset timer
            return;
        }
    }
    return;
}