// FUNC_NAME: ControllerState::update
void __thiscall ControllerState::update(int param1) {
    // param1 is 'this' pointer to a ControllerState object.
    // Offsets: +0x00 = vtable? +0x04 = pointer to something (maybe parent controller)
    // +0x10 = flags (uint32), +0x44 = accumulated value (float), +0x4c = current deadZoneState,
    // +0x5c = pointer to active stick data (position), +0x60 = bool isActive, +0x68 = additive value (float).

    char isConnected = FUN_00711510();          // Check if a controller is connected
    float maxAccum = _DAT_00d5780c;             // Global maximum accumulation value (clamp)

    if (isConnected) {
        if ((*(char *)(param1 + 0x60) == '\0') && (*(int *)(param1 + 0x5c) != 0)) {
            // If inactive but has active stick data, accumulate position + additive
            float accum = *(float *)(*(int *)(param1 + 0x5c) + 0x14)  // stick position X component? (offset 0x14)
                         + *(float *)(param1 + 0x68)                  // global additive
                         + *(float *)(param1 + 0x44);                // current accumulator
            *(float *)(param1 + 0x44) = accum;
            if (maxAccum < accum) {
                *(float *)(param1 + 0x44) = maxAccum; // clamp to max
            }
            // Set flag bit 7 (0x80) – indicates accumulated value changed?
            *(uint *)(param1 + 0x10) = *(uint *)(param1 + 0x10) | 0x80;
        }
        *(char *)(param1 + 0x60) = 1; // Mark as active
    }

    // DeadZone state machine: based on global thresholds and previous state
    if ((_DAT_00e51748 >= 0.0f) || ((*(uint *)(param1 + 0x10) >> 4 & 1) == 0) || ((*(uint *)(param1 + 0x10) >> 3 & 1) != 0)) {
        // Normal dead zone processing
        if ((DAT_00e51744 < 0.0f) || ((*(int *)(param1 + 0x4c) == 3) && (DAT_00e51744 * DAT_00d5f378 < 0.0f))) {
            *(int *)(param1 + 0x4c) = 3; // State 3 (down? or right?)
        } else if ((DAT_00e51740 < 0.0f) || ((*(int *)(param1 + 0x4c) == 2) && (DAT_00e51740 * DAT_00d5f378 < 0.0f))) {
            *(int *)(param1 + 0x4c) = 2; // State 2
        } else if ((DAT_00e5173c < 0.0f) || ((*(int *)(param1 + 0x4c) == 1) && (DAT_00e5173c * DAT_00d5f378 < 0.0f))) {
            *(int *)(param1 + 0x4c) = 1; // State 1
        } else {
            *(int *)(param1 + 0x4c) = 0; // Neutral
        }
    } else {
        *(int *)(param1 + 0x4c) = 4; // Special state 4 (likely inactive/disconnected)
    }

    // If not in neutral state OR still active, check for early exit conditions
    if ((*(int *)(param1 + 0x4c) != 0) || (*(char *)(param1 + 0x60) == '\0')) {
        // Check global flags: if bit 12 of parent object (offset 0x1f58) is set, skip cleanup
        if ((*(uint *)(*(int *)(param1 + 4) + 0x1f58) >> 12 & 1) != 0) {
            return;
        }
        char isPaused = FUN_007174e0(); // Check for pause/menu overlay
        if (isPaused != false) {
            return;
        }
    }

    // Cleanup: release active stick data if present
    if (*(int *)(param1 + 0x5c) != 0) {
        FUN_0071bc70(*(int *)(param1 + 0x5c)); // Release or deallocate stick data
        *(int *)(param1 + 0x5c) = 0;
    }
    *(char *)(param1 + 0x60) = 0; // Mark as inactive
}

// Global variables (declared elsewhere)
extern float _DAT_00d5780c;        // Max accumulation constant
extern float _DAT_00e51748;        // DeadZone threshold 1
extern float DAT_00e51744;         // DeadZone threshold 2
extern float DAT_00e51740;         // DeadZone threshold 3
extern float DAT_00e5173c;         // DeadZone threshold 4
extern float DAT_00d5f378;        // Sensitivity multiplier

// Called functions (assumed names)
bool __fastcall FUN_00711510();         // e.g., isControllerConnected
bool __fastcall FUN_007174e0();         // e.g., isGamePaused
void __fastcall FUN_0071bc70(void*);    // e.g., releaseStickData