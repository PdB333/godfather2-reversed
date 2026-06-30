// FUNC_NAME: ChaseCamera::updateCamera

// 0x006c5a60 - Updates camera position relative to look-at target with rotation, easing, and damping

#include <math.h>

// External globals used by this function
extern float DAT_00d5780c; // Some threshold constant
extern float DAT_00e44564; // Another constant (probably max offset)
extern float DAT_00e445c8; // Time scaling constant

// Helper function signatures (derived from decompiled callees)
extern void quaternionToMatrix(float quat, float matrix[3]); // FUN_00424fb0 - converts heading to a 3x1 direction matrix
extern void rotateVectorByMatrix(const float* input, const float* matrix, float* output); // FUN_006c4390
extern float getFrameDeltaTime(); // FUN_006c3c90 - returns elapsed time in seconds
extern float applySmoothStep(float t); // FUN_004a1580 - smooth step interpolation
extern void rotateWorldVector(const float* vec, const float* axis, float angle, float* result); // FUN_004a0370
extern float computeDampingFactor(int cameraMode, int unk1, int unk2, float unk3, float unk4, float ratio); // FUN_006c91c0
extern float fastAbs(double x); // FUN_00b9a9fa - might be fabs or a fast approximation
extern void clampCameraTargetOffset(void* camera); // FUN_006c4f00
extern void copyVector(const float* src, float* dst); // FUN_006ca5e0 - copies a 3-vector

// Class member offsets (hypothetical layout for ChaseCamera)
// +0x80: float springBias
// +0x108: float totalDistance
// +0x10c: float currentDistance
// +0x208: float cameraOffset[3] (stored for clamping)
// +0x214: float cameraPos[3]
// +0x220: float lookAtPos[3]
// +0x238: float targetPos[3]
// +0x24c: float interpolatedPos[3] (intermediate for smoothing)
// +0x284: float rotationSpeed
// +0x2b0: float additiveOffset1
// +0x2ec: float additiveOffset2
// +0x298: int cameraModeId

void __thiscall ChaseCamera::updateCamera(float heading) {
    float rotationMatrix[3]; // 12-byte matrix (3 floats? Actually stored as 3 floats representing a direction?)
    quaternionToMatrix(heading, rotationMatrix);

    // Compute forward direction from lookAt and rotation
    float forward[3]; // local_30, local_2c, local_28
    rotateVectorByMatrix(&lookAtPos[0], rotationMatrix, forward);

    // Get delta time and apply easing to angle
    float dt = getFrameDeltaTime();
    float easedAngle = applySmoothStep(dt * DAT_00e445c8 + rotationSpeed);

    // Compute axis perpendicular to forward (simplified cross product)
    float axis[3];
    axis[0] = -forward[2];          // local_24 = local_2c*0 - local_28
    axis[1] = 0.0f;                 // local_20 = local_28*0 - local_30*0
    axis[2] = forward[0];           // local_1c = local_30 - local_2c*0

    // Rotate forward by eased angle around the perpendicular axis
    rotateWorldVector(forward, axis, easedAngle, forward);

    // Compute distance ratio and damping factor
    float distanceRatio = currentDistance / totalDistance; // +0x10c / +0x108
    float damping = computeDampingFactor(cameraModeId, 0, 0, 1.0f, 1.0f, distanceRatio);

    // Calculate offset scaling
    float scaledOffset = ((damping - DAT_00d5780c) * springBias + DAT_00d5780c) *
                         (additiveOffset2 + additiveOffset1);

    // Set new camera position = lookAt + forward * scaledOffset
    cameraPos[0] = scaledOffset * forward[0] + lookAtPos[0];
    cameraPos[1] = scaledOffset * forward[1] + lookAtPos[1];
    cameraPos[2] = scaledOffset * forward[2] + lookAtPos[2];

    // Compute absolute deltas for clamping
    float dx = cameraPos[0] - lookAtPos[0];
    float dy = cameraPos[1] - lookAtPos[1];
    // Note: original code stores dy as double, then takes fastAbs, but stores as float
    cameraOffset[0] = fastAbs((double)dy);              // +0x208
    cameraOffset[1] = fastAbs((double)(DAT_00e44564 - dx)); // +0x20c
    cameraOffset[2] = 0.0f;                              // +0x210

    // Apply constraints and copy target to interpolated position
    clampCameraTargetOffset(this);
    copyVector(&targetPos[0], &interpolatedPos[0]); // FUN_006ca5e0(this+0x24c, this+0x238, this+0x238)
}