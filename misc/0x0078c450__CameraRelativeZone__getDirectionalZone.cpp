// FUNC_NAME: CameraRelativeZone::getDirectionalZone

#include <cmath>

// Forward declarations of external game functions
// FUN_00471610: Returns pointer to a camera manager structure
float* getCameraManager();
// FUN_0056afa0: Normalizes a 3D vector in-place
void normalizeVector(float* vec);

// Global constants for directional thresholds (from game data)
extern const float ZONE_THRESHOLD_FRONT;      // DAT_00d69a74
extern const float ZONE_THRESHOLD_FRONT_SIDE; // DAT_00d69a78
extern const float ZONE_THRESHOLD_SIDE_BACK;  // DAT_00d69a7c
extern const float ZONE_THRESHOLD_BACK;       // DAT_00d69a80
extern const float ZONE_CROSS_COMP;           // _DAT_00d577a0 – small epsilon or zero for cross product sign test

enum DirectionalZone : char {
    ZONE_NONE        = 0x00,
    ZONE_BACK_LEFT   = 0x01,
    ZONE_BACK_RIGHT  = 0x02,
    ZONE_FRONT       = 0x03,
    ZONE_FRONT_LEFT  = 0x04,
    ZONE_FRONT_RIGHT = 0x05,
    ZONE_SIDE_LEFT   = 0x06,
    ZONE_SIDE_RIGHT  = 0x07
};

// Function at address 0x0078c450
// Takes a 3D direction vector (param_1) and returns the directional zone (0-7)
// relative to the current camera forward vector.
char getDirectionalZone(const float* inputDir) {
    // Get camera forward vector from manager at +0x20, +0x24, +0x28
    float* cameraMgr = getCameraManager();
    float camForward[3];
    camForward[0] = *(float*)((char*)cameraMgr + 0x20);
    camForward[1] = *(float*)((char*)cameraMgr + 0x24);
    camForward[2] = *(float*)((char*)cameraMgr + 0x28);

    // Normalize the camera forward direction
    normalizeVector(camForward);

    // Compute dot product: inputDir · camForward
    float dot = inputDir[0] * camForward[0] +
                inputDir[1] * camForward[1] +
                inputDir[2] * camForward[2];

    // Compute sign of cross product (z * fx - x * fz) to determine left/right
    bool isRightSide = ZONE_CROSS_COMP < (inputDir[0] * camForward[2] - inputDir[2] * camForward[0]);

    // Determine zone based on dot product thresholds
    if (dot > ZONE_THRESHOLD_FRONT) {
        return ZONE_FRONT; // 0x03
    } else if (dot > ZONE_THRESHOLD_FRONT_SIDE) {
        return isRightSide ? ZONE_FRONT_RIGHT : ZONE_FRONT_LEFT;
    } else if (dot > ZONE_THRESHOLD_SIDE_BACK) {
        return isRightSide ? ZONE_SIDE_RIGHT : ZONE_SIDE_LEFT;
    } else if (dot > ZONE_THRESHOLD_BACK) {
        return isRightSide ? ZONE_BACK_RIGHT  : ZONE_BACK_LEFT;
    } else {
        return ZONE_NONE;
    }
}