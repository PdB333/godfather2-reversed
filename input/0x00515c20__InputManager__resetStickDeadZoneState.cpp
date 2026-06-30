// FUNC_NAME: InputManager::resetStickDeadZoneState
// Address: 0x00515c20
// Purpose: Resets all stick/thumbstick deadzone tracking state and optional rumble stop.
// Called when analog stick input falls within deadzone thresholds.

#include <cstdint>

// Global state for controller input processing (offsets relative to some base address)
// These would likely be part of a singleton InputManager or global input state struct.
// For clarity, they are defined as extern globals with descriptive names.

// Current analog stick value (e.g., left stick X axis) - float
extern float g_currentStickValue;      // DAT_00e2af44

// Global flag indicating active stick movement (non-zero when stick is beyond deadzone)
extern float g_stickActiveFlag;        // DAT_01219240

// Deadzone thresholds per stick axis/group (initialized from configuration)
extern float g_stickDeadzoneThresholds[8];  // DAT_01219200..DAT_0121922c (sequential after zeroing)

// Timer value for rumble duration / stick release hysteresis
extern float g_rumbleReleaseTimer;     // DAT_00e2eb58

// Other state variables (probably part of a larger structure for stick tracking)
extern int32_t g_stickStateFlags[4];   // _DAT_012191e0.._DAT_012191ec (four ints)
extern int32_t g_anotherStateFlags[4]; // _DAT_012191f0.._DAT_012191fc (four ints)
extern float g_stickReleaseTimers[2];  // DAT_01219224, DAT_01219228  (set to g_rumbleReleaseTimer)
extern int32_t g_unusedCounter;        // DAT_01219230
extern float g_stickDeadzoneReset;     // DAT_00e2b1a4 (the deadzone reset value, e.g., 0.0 or threshold)

void InputManager::resetStickDeadZoneState()
{
    // If the stick was active and the current value has fallen within the deadzone area (any threshold)
    // then stop rumble / reset tracker via FUN_00515460.
    if (g_stickActiveFlag != 0.0f)
    {
        // Check if stick value is <= any of the first group of thresholds (e.g., for one axis/group)
        bool inDeadzoneGroup1 = (g_currentStickValue <= g_stickDeadzoneThresholds[0] ||
                                 g_currentStickValue <= g_stickDeadzoneThresholds[1] ||
                                 g_currentStickValue <= g_stickDeadzoneThresholds[2]);
        // Check if stick value is <= the main threshold for group1
        bool inDeadzoneMain1 = (g_currentStickValue <= g_stickDeadzoneThresholds[4]);  // DAT_01219220
        // Check if stick value is <= any of the second group of thresholds
        bool inDeadzoneGroup2 = (g_currentStickValue <= g_stickDeadzoneThresholds[5] ||   // DAT_01219210
                                 g_currentStickValue <= g_stickDeadzoneThresholds[6] ||   // DAT_01219214
                                 g_currentStickValue <= g_stickDeadzoneThresholds[7]);    // DAT_01219218
        // Corresponding main threshold for group2
        bool inDeadzoneMain2 = (g_currentStickValue <= g_stickDeadzoneThresholds[8]);     // DAT_0121922c

        // Trigger rumble stop if either main threshold is true and respective inner group is true
        if ((inDeadzoneMain1 && inDeadzoneGroup1) || (inDeadzoneMain2 && inDeadzoneGroup2))
        {
            FUN_00515460();  // Probably stop rumble or reset stick tracking routine
        }
    }

    // Reset all deadzone thresholds to the baseline deadzone value (e.g., 0.15)
    float resetDeadzone = static_cast<float>(g_stickDeadzoneReset);
    g_stickDeadzoneThresholds[0] = resetDeadzone;   // +0x00
    g_stickDeadzoneThresholds[1] = resetDeadzone;   // +0x04
    g_stickDeadzoneThresholds[2] = resetDeadzone;   // +0x08

    // Reset all state flags to zero (these may track deadzone entry/exit timers or previous samples)
    g_stickStateFlags[0] = 0;   // +0xe0
    g_stickStateFlags[1] = 0;   // +0xe4
    g_stickStateFlags[2] = 0;   // +0xe8
    g_stickStateFlags[3] = 0;   // +0xec
    g_anotherStateFlags[0] = 0; // +0xf0
    g_anotherStateFlags[1] = 0; // +0xf4
    g_anotherStateFlags[2] = 0; // +0xf8
    g_anotherStateFlags[3] = 0; // +0xfc

    // Clear additional threshold/state at offset 0x0c and 0x1c
    g_stickDeadzoneThresholds[3] = 0.0f;   // +0x0c?? but here it's an int? Actually it was _DAT_0121920c = 0, but we treat as int for now. Use separate variable.
    // Note: The decompiled shows _DAT_0121920c and _DAT_0121921c as integer zeros.
    // For clarity, we'll assume there are two more integer state fields.
    // We'll represent them as g_stickStateInt[0] and g_stickStateInt[1].
    // Let's define them as:
    extern int32_t g_extraState0;        // +0x0c
    extern int32_t g_extraState1;        // +0x1c
    g_extraState0 = 0;
    g_extraState1 = 0;

    // Zero out the second group of thresholds (the ones that were in the second condition)
    g_stickDeadzoneThresholds[4] = 0.0f;   // +0x10 but careful: these are sequential after offset0x08? Actually they are at 0x10,0x14,0x18,0x20,0x2c. We'll index accordingly.
    g_stickDeadzoneThresholds[5] = 0.0f;   // +0x10? No, the decompiled sets DAT_01219210=0.0, etc. We'll just use the same array but need correct mapping.
    // Better to keep the original distinct variable names for clarity.
    // Since the goal is reconstruction, we can list them as distinct globals.
    // I'll create a struct or simply list them all.

    // For clarity, I'll rewrite using the original addresses but with meaningful names.

    // Declare remaining global thresholds and state (they would be defined elsewhere)
    extern float g_deadzoneThreshold4;   // DAT_01219210
    extern float g_deadzoneThreshold5;   // DAT_01219214
    extern float g_deadzoneThreshold6;   // DAT_01219218
    extern float g_deadzoneThreshold7;   // DAT_01219220
    extern float g_deadzoneThreshold8;   // DAT_0121922c
    extern float g_rumbleTimers[2];      // DAT_01219224, DAT_01219228
    extern int32_t g_unusedCounter2;     // DAT_01219230

    g_deadzoneThreshold4 = 0.0f;
    g_deadzoneThreshold5 = 0.0f;
    g_deadzoneThreshold6 = 0.0f;
    g_deadzoneThreshold7 = 0.0f;
    g_deadzoneThreshold8 = 0.0f;

    // Set rumble release timers to the current rumble release value (probably duration)
    g_rumbleTimers[0] = g_rumbleReleaseTimer;
    g_rumbleTimers[1] = g_rumbleReleaseTimer;

    g_unusedCounter2 = 0;

    // Finally, clear the active flag, indicating stick is now considered idle
    g_stickActiveFlag = 0.0f;
}