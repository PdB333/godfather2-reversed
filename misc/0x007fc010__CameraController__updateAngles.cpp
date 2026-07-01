// FUNC_NAME: CameraController::updateAngles
// Function address: 0x007fc010
// This function updates camera or vehicle orientation angles with clamping and interpolation.
// It uses a state structure containing pointers to angle arrays and limits.

#include <cstdint>

// Forward declarations of called functions
void vectorSubtract(float* out, float a, float b); // FUN_007f69a0 - computes direction vector
void extractAngles(const float* vec, float* angle1, float* angle2, float* angle3); // FUN_0056c180 - extracts euler angles from vector
float normalizeAngle(float value, float range); // FUN_0056aee0 - normalizes angle to range (e.g., 2*PI)
void debugBreak(); // FUN_007ef560 - debug break or error handler
void debugDrawLine(void* target, int color, float* points, int count); // FUN_00470b10 - draws debug line

// Global constants (from data references)
extern float _DAT_00d5780c; // e.g., current time
extern float DAT_00e44564; // max angle limit
extern float DAT_00d5d70c; // angle normalization range (likely 2*PI)
extern float DAT_00d71e78; // threshold for debug trigger
extern uint32_t DAT_00e44680; // mask or value for debug condition
extern float DAT_00e44748; // scale factor for debug drawing
extern void* DAT_01131ee0; // debug render target

// Class definition based on offsets used
class CameraController {
public:
    // Offsets used:
    // +0x970: uint32 flags1 (bit 0xb used)
    // +0x974: uint32 flags2 (bit 0xb used)
    // +0xfd8: float overrideAngle1
    // +0xfdc: float overrideAngle2
    // +0x1bc8: SomeObject* debugObject (has byte at +0x5e2)
    // +0xfd4: int debugFlag

    uint32_t flags1; // +0x970
    uint32_t flags2; // +0x974
    float overrideAngle1; // +0xfd8
    float overrideAngle2; // +0xfdc
    void* debugObject; // +0x1bc8
    int debugFlag; // +0xfd4

    void updateAngles(void* arg2, float* state, float deltaTime);
};

// State structure (param_3) - mixed floats and pointers
struct CameraState {
    float angle0; // [0] - base angle
    float angle1; // [1] - target angle difference
    float pad2;   // [2]
    float pad3;   // [3]
    float* anglePtr; // [4] - pointer to float array (at least 3 elements)
    float dirX;   // [5] - direction component
    float pad6;   // [6]
    float dirY;   // [7] - direction component
    float* limitPtr; // [8] - pointer to float array (at least 2 elements: min, max)
    float pad9;   // [9]
    float pad10;  // [10]
    float resultAngle1; // [11] - written at end
    float resultAngle2; // [12] - written at end
};

void CameraController::updateAngles(void* arg2, float* stateRaw, float deltaTime) {
    CameraState* state = reinterpret_cast<CameraState*>(stateRaw);
    float local_84, local_80, local_7c, local_78, local_74, local_70, local_6c, local_64;
    float local_68, fStack_60;
    float local_58, local_5c;
    float local_54[4]; // unused?
    float local_50[3]; // vector buffer

    // Initialize locals (from decompiler)
    // local_44, local_34, local_24 set to 0 (unused)
    // local_14 = _DAT_00d5780c (time) - not used later? Possibly used in called functions.

    // Compute direction vector from state->dirX and state->dirY
    vectorSubtract(local_50, state->dirX, state->dirY);

    // Extract angles from the direction vector
    extractAngles(local_50, &local_58, &local_5c, local_54);

    // Get limit values from the pointer at state->limitPtr
    float* limitArray = reinterpret_cast<float*>(state->limitPtr);
    local_7c = limitArray[1]; // max limit for angle2?
    local_74 = limitArray[0]; // min limit for angle1?

    // Compute clamped bounds
    local_78 = DAT_00e44564 - local_7c;
    local_70 = DAT_00e44564 - local_74;

    // Get current angles from the pointer at state->anglePtr
    float* angleArray = reinterpret_cast<float*>(state->anglePtr);
    local_6c = angleArray[0]; // current angle1
    local_64 = angleArray[2]; // current angle3? (third component)

    // Compute angle differences
    float diffAngle1 = local_58 - state->angle0;
    local_80 = normalizeAngle(diffAngle1, DAT_00d5d70c);
    local_84 = local_5c - state->angle1;

    // Check override flags
    if (((this->flags1 >> 0xb) & 1) && ((this->flags2 >> 0xb) & 1)) {
        local_84 = this->overrideAngle1;
        local_80 = this->overrideAngle2;
    }

    // Time difference
    local_68 = _DAT_00d5780c - deltaTime;

    // Interpolate new angles
    float newAngle1 = local_68 * local_6c + local_80 * deltaTime;
    float newAngle2 = local_68 * local_64 + local_84 * deltaTime;
    local_80 = normalizeAngle(newAngle1, DAT_00d5d70c);
    local_84 = normalizeAngle(newAngle2, DAT_00d5d70c);

    // Clamp local_84 between local_7c and local_78
    if (local_84 <= local_7c) {
        if (local_78 <= local_84) {
            // within range, keep local_84
        } else {
            local_84 = local_78;
        }
    } else {
        local_84 = local_7c;
    }

    // Clamp local_80 between local_74 and local_70
    if (local_80 <= local_74) {
        if (local_70 <= local_80) {
            // within range, keep local_80
        } else {
            local_80 = local_70;
        }
    } else {
        local_80 = local_74;
    }

    // Debug condition: if difference exceeds threshold and debugObject exists
    if ((static_cast<float>(static_cast<uint32_t>(local_80 - local_6c) & DAT_00e44680) > DAT_00d71e78) &&
        (this->debugObject != nullptr)) {
        debugBreak();
    }

    // Write back to angle array
    angleArray[0] = local_80;
    angleArray[2] = local_84;
    state->resultAngle1 = angleArray[0];
    state->resultAngle2 = angleArray[2];

    // Debug drawing if enabled
    if ((*(reinterpret_cast<char*>(this->debugObject) + 0x5e2) != '\0') || (this->debugFlag != 0)) {
        float debugPoints[2];
        debugPoints[0] = local_80 * DAT_00e44748;
        debugPoints[1] = local_84 * DAT_00e44748;
        debugDrawLine(&DAT_01131ee0, 0, debugPoints, 2);
    }
}