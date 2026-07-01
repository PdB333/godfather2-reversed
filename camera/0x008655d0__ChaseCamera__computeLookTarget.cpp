// FUNC_NAME: ChaseCamera::computeLookTarget
#include <cmath>

// Offset constants for the object's internal state
// +0xfd4: m_currentAimProgress (float)
// +0x1148: m_yawAngle (float)
// +0xfc4: m_aimSpeed (float)

// Global tuning constants (from .rdata)
static const float kBaseAimAdjust = DAT_00d5eee4;      // base offset for aiming
static const float kNegativeAimAdjust = DAT_00d5ef70;  // offset if aim progress negative
static const float kTruncAdjust = DAT_00e44578;        // adjust for negative truncation (likely 1.0f)
static const float kSpeedMultiplier = DAT_00d75750;    // multiplier applied to integer part of input

// External helper functions (assembly stubs)
char FUN_00865000(void* transform, float* outX, float* outY, float* outZ, void* outExtra);
void* FUN_00471610();  // returns a pointer to the active transform/camera data
double FUN_00b99e20(); // cos? (called before sin)
double FUN_00b99fcb(); // sin?

void ChaseCamera::computeLookTarget(float inputParam, float outVec[3])
{
    // ----------------------------------------------------------------
    // 1. Determine base adjustment based on current aim progress
    // ----------------------------------------------------------------
    float aimProgress = *(float*)((uintptr_t)this + 0xfd4);
    float absProgress = fabsf(aimProgress);

    float temp = inputParam;
    float adjustment = kBaseAimAdjust;

    // NOTE: bitwise comparison avoids NaN issues; interpret as float magnitude comparison
    if (fabsf(aimProgress) <= inputParam) {
        temp = absProgress;
        // Check sign of aimProgress using integer reinterpret
        if ((int&)aimProgress < 0) {
            adjustment = kNegativeAimAdjust;
        }
    }

    // ----------------------------------------------------------------
    // 2. Compute interpolation factor ("speed") from input/time
    // ----------------------------------------------------------------
    int intPart = (int)temp;
    float intFrac = (float)intPart;
    if (temp < 0.0f) {
        intFrac += kTruncAdjust; // floor for negative numbers
    }
    float speed = intFrac * kSpeedMultiplier + adjustment;

    // ----------------------------------------------------------------
    // 3. Try to get precise aim target via raycast / projection
    // ----------------------------------------------------------------
    void* cameraTransform = FUN_00471610();
    // CameraTransform+0x30 is the camera world transform (3 floats for position?)
    float outX, outY, outZ;
    void* outExtra; // unused here
    char raySuccess = FUN_00865000((char*)cameraTransform + 0x30, &outX, &outY, &outZ, &outExtra);

    if (raySuccess != 0 && outY >= 0.0f) {
        // ------------------------------------------------------------
        // Successful ray: use projected point and apply angular offset
        // ------------------------------------------------------------
        float yawAngle = *(float*)((uintptr_t)this + 0x1148);
        outVec[1] = outY;  // Y is set directly

        if (speed == 0.0f) {
            outVec[0] = outX;
            outVec[2] = outZ;
            return;
        }

        // Rotate the point around the Y axis by yawAngle, scaled by speed
        double cosA = FUN_00b99e20(); // cos(yawAngle) – assumed
        double sinA = FUN_00b99fcb(); // sin(yawAngle)
        outVec[0] = outX - (float)cosA * speed;
        outVec[2] = (float)sinA * speed + outZ;
        return;
    }

    // ----------------------------------------------------------------
    // 4. Fallback: use camera position and interpolate toward target
    // ----------------------------------------------------------------
    // First, copy the raw camera position
    float* camPos = (float*)((uintptr_t)FUN_00471610() + 0x30);
    outVec[0] = camPos[0];
    outVec[1] = camPos[1];
    outVec[2] = camPos[2];

    // Then interpolate toward another transform (maybe the character position)
    float* targetPos = (float*)FUN_00471610(); // different transform?
    float blendFactor = *(float*)((uintptr_t)this + 0xfc4) - speed;
    outVec[0] = targetPos[0] * blendFactor + outVec[0];
    outVec[1] = targetPos[1] * blendFactor + outVec[1];
    outVec[2] = targetPos[2] * blendFactor + outVec[2];
}