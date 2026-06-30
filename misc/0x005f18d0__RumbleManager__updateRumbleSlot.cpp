// FUNC_NAME: RumbleManager::updateRumbleSlot
// Address: 0x005f18d0
// Handles updating rumble/vibration for a single slot on a controller.
// param_1: RumbleSlot* - contains slot index (byte[3]) and motor ID (int[4]) 
// param_2: ControllerState* - contains controller input state and vibration settings

#include <cstdint>

// Constants (from DAT references)
static constexpr float RUMBLE_MASTER_SCALE = 1.0f; // DAT_00e2b1a4
static constexpr float RUMBLE_JITTER_FACTOR = 0.1f; // DAT_00e2b04c (example value)
static constexpr float RUMBLE_EPSILON = 0.0001f; // DAT_00e2fc48
static constexpr float RUMBLE_DECAY_THRESHOLD = 0.8f; // DAT_00e2b05c

// Known external functions (prototypes)
bool isSoundMuted(void* soundManager, int flag); // FUN_005dcb60
bool isRumbleSupported(); // FUN_005f3240
float randomFloat(); // FUN_00427180
void setRumbleMotor(int slotIndex, int motorId, int duration, float leftSpeed, float rightSpeed); // FUN_005dbc10 (5 args)
void setRumbleMotor(int slotIndex, int motorId, int duration, float speed); // FUN_005dbc10 (4 args, overload)
void setBothMotors(uint8_t magnitude, float speed); // FUN_005f34f0

struct RumbleSlot {
    uint8_t slotIndex; // +0x03
    int32_t motorId;   // +0x04 (actually a byte, extended to int)
};

struct ControllerSettings {
    uint32_t flags;         // +0x08
    float maxMagnitude;     // +0x20
    float rumbleTime;       // +0x10
    float jitterAmount;     // +0x14
};

struct ControllerState {
    int* someList;             // +0x2c
    uint16_t* rumbleCounts;    // +0x30 (array of count per slot)
    ControllerSettings* settings; // +0x08 (pointer to settings)
    float leftMotorSpeed;      // +0x50
    uint16_t flags;            // +0x4a (byte, but used as ushort)
    float rumbleTimer;         // +0x7c
    float rightMotorSpeed;     // +0x3c
};

void RumbleManager::updateRumbleSlot(RumbleSlot* slot, ControllerState* controller) {
    if (!slot || !controller) return;

    uint16_t* rumbleCounts = controller->rumbleCounts;
    int* someList = controller->someList;
    ControllerSettings* settings = controller->settings;

    // Validate slot index against rumble count array
    if (rumbleCounts == (uint16_t*)0xdeadbeef) return;
    if (slot->slotIndex >= rumbleCounts[0]) return; // *rumbleCounts is count? assuming first element is count
    if (rumbleCounts + slot->slotIndex * 0x4a + 2 == nullptr) return; // complex offset, probably checking if slot is valid

    uint32_t settingsFlags = settings->flags;
    float leftSpeed = RUMBLE_MASTER_SCALE;

    // If there's an entity associated and sound is not muted, scale rumble down
    if (someList && *someList != 0) {
        // DAT_01223508 is a global sound manager pointer
        if (isSoundMuted(*(void**)0x01223508, someList[0x17])) {
            leftSpeed = 0.0f;
        }
    }

    leftSpeed *= controller->leftMotorSpeed; // Already set? Or master gain

    // Compute duration based on motorId (shifted by 7)
    int duration = (int)((float)(slot->motorId << 7) * leftSpeed);
    int16_t sDuration = (int16_t)duration;

    // Check if rumble should be applied
    if (sDuration > 0 || !(settingsFlags & 0x20)) { // flag bit 5 (0x20) disables negative durations?
        if (!isRumbleSupported()) {
            // Fallback: just rumble with no right motor
            setRumbleMotor(slot->slotIndex, slot->motorId, sDuration, leftSpeed);
            return;
        }

        // Compute left motor magnitude (clamped 0-127)
        uint8_t magnitude = (uint8_t)((float)slot->motorId * settings->maxMagnitude);
        if (magnitude == 0) {
            magnitude = 0;
        } else if (magnitude < 0x7f) {
            magnitude = magnitude; // already clamped
        } else {
            magnitude = 0x7f;
        }

        // Determine right motor speed jitter
        float rightSpeed = RUMBLE_MASTER_SCALE; // default
        if (!(controller->flags & 2)) { // flag bit 1 (low frequency motor only)
            if (settings->rumbleTime > 0.0f) {
                // Add random jitter if not already set
                if (!(settings->flags & 4) || controller->rumbleTimer == 0.0f) {
                    controller->rumbleTimer = randomFloat();
                }
                rightSpeed = settings->rumbleTime * controller->rumbleTimer * RUMBLE_JITTER_FACTOR +
                             (RUMBLE_MASTER_SCALE - settings->rumbleTime);
            }
        } else {
            rightSpeed = controller->rightMotorSpeed; // explicit right speed
        }

        // Apply initial rumble with both motors
        setRumbleMotor(slot->slotIndex, slot->motorId, sDuration, (double)leftSpeed, (double)rightSpeed);

        // Second rumble application (high frequency?) with decay
        if (settings->jitterAmount > 0.0f) {
            if (!(settings->flags & 8) || controller->rumbleTimer == 0.0f) {
                float random = randomFloat();
                float factor = 1.0f - random * settings->jitterAmount;
                if (fabs(factor - controller->rumbleTimer) >= RUMBLE_EPSILON) {
                    if (factor - controller->rumbleTimer <= RUMBLE_DECAY_THRESHOLD) {
                        factor = controller->rumbleTimer - RUMBLE_EPSILON;
                    } else {
                        factor = controller->rumbleTimer + RUMBLE_EPSILON;
                    }
                }
                controller->rumbleTimer = factor;
            }
            // Recompute magnitude with updated timer
            magnitude = (uint8_t)((float)slot->motorId * settings->maxMagnitude * controller->rumbleTimer);
            if (magnitude == 0) {
                magnitude = 0;
            } else if (magnitude < 0x7f) {
                // already clamped
            } else {
                magnitude = 0x7f;
            }
        }

        // Apply combined rumble
        setBothMotors(magnitude, rightSpeed);
        controller->flags = 0; // Clear flags after processing
    }
}