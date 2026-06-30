// FUNC_NAME: PlayerAimSystem::updateAimTarget

// 0x004c6400 - Updates aim target based on input (keyboard/controller) and global settings.
// This function sets multiple aim-related vectors on the object (this), reading from
// either keyboard (via FS segment) or controller analog sticks.

#include <cstdint>

// Forward declarations of external functions (not implemented here)
void setVector(void* context, float* targetVec, const float* srcVec);   // FUN_0060add0
void applyAimRecoil();                                                   // FUN_006063b0
float getAimTargetFromSystem();                                         // FUN_0041f560
void setSystemTarget(void* context, float* targetVec, float value);     // FUN_0060b020

// Global variables (reverse-engineered)
extern void* g_gameData;               // DAT_012233b0 - main game singleton
extern bool g_bControllerConnected;    // DAT_01163840
extern int32_t g_activeControllerIndex; // DAT_01163830
extern uint8_t g_controllerStateArray[0x1000 * 0x38]; // DAT_011a0f28, 0x38 bytes per controller
extern float g_aimSensitivity;          // DAT_00e44640
extern float g_defaultAimOffset;        // DAT_00e2b1a4 (baseline for aim)
extern float g_defaultAimVecKeyboard[]; // DAT_00e2e760 (probably 3 floats)
extern float g_defaultAimVecController[]; // DAT_01163810
extern float g_anotherDefaultKeyboard[]; // DAT_00e2e720
extern float g_anotherDefaultController[]; // DAT_011637d0

// Assumed structure for this object (offsets in bytes)
struct AimSystemData {
    int32_t field_0;      // +0x00 flag (non-zero triggers recoil/reset)
    float* targetVec1;    // +0x04 pointer to vector? (used with setVector)
    float* targetVec2;    // +0x08 pointer to vector?
    float* targetVec3;    // +0x0C pointer to vector?
    float* aimOffsetVec;  // +0x10 pointer to aim offset vector
};

void __thiscall FUN_004c6400(AimSystemData* thisPtr, void* context) {
    float x, y, z, w; // stack locals: local_20, local_1c, local_18, local_14

    // Check if player manager exists and controller is connected
    if (*(void**)((uint8_t*)g_gameData + 0x30) != nullptr && g_bControllerConnected) {
        // --- Keyboard input (via FS segment PEB) ---
        // Read a byte from keyboard state array: FS:0x2c => PEB, +8 => some structure, +0x9b => key state?
        // The offset is computed from player manager (+0x18). This is likely the current keyboard input delta.
        uint8_t* pebBase = (uint8_t*)__readfsdword(0x2c);
        int32_t keyboardOffset = *(int32_t*)(*(int32_t*)(*(int32_t*)(pebBase + 8) + 8) + 0x9b + 
                                             *(int32_t*)(*(int32_t*)(*(uint8_t*)g_gameData + 0x30) + 0x18));
        float keyDelta = (float)(*(uint8_t*)keyboardOffset) * g_aimSensitivity; // +0x30

        // --- Controller analog input ---
        const uint8_t* controllerState = nullptr;
        if (g_activeControllerIndex < 0x1000) {
            controllerState = g_controllerStateArray + (g_activeControllerIndex * 0x38);
        }

        if (controllerState != nullptr) {
            // Analog sticks (2 bytes each, little-endian)
            x = (float)(*(uint16_t*)(controllerState + 2)); // local_20
            y = (float)(*(uint16_t*)(controllerState + 4)); // local_1c
        } else {
            x = 0.0f;
            y = 0.0f;
        }
        z = g_defaultAimOffset - keyDelta; // local_18

        // Set aim offset vector (thisPtr->aimOffsetVec) from (x, y, z)
        setVector(context, thisPtr->aimOffsetVec, &x);

        // If flag is set, apply recoil/reset
        if (thisPtr->field_0 != 0) {
            applyAimRecoil();
        }

        // Set target vectors (1 and 3) depending on controller connection
        if (g_bControllerConnected) {
            setVector(context, thisPtr->targetVec1, g_defaultAimVecController);
        } else {
            setVector(context, thisPtr->targetVec1, g_defaultAimVecKeyboard);
        }

        // Get a target value from system and set target2
        float sysTarget = getAimTargetFromSystem();
        setSystemTarget(context, thisPtr->targetVec2, sysTarget);

        // Set target3 similarly
        if (g_bControllerConnected) {
            setSystemTarget(context, thisPtr->targetVec3, g_anotherDefaultController[0]);
        } else {
            setSystemTarget(context, thisPtr->targetVec3, g_anotherDefaultKeyboard[0]);
        }
    } else {
        // No controller connected: set aim offset to default (only Z offset, X and Y = default offset)
        x = g_defaultAimOffset;
        y = g_defaultAimOffset;
        z = g_defaultAimOffset;
        w = 0.0f;
        setVector(context, thisPtr->aimOffsetVec, &x);
    }
}