// FUNC_NAME: analogInputProcessor
// Function address: 0x0041e7e0
// Role: Processes a 3-component analog input vector (e.g., thumb stick or accelerometer)
// with dead-zone clamping and prepares interpolation data for smoothing.
// Uses a threshold (gSmoothThreshold) and time constant (gTimeConstant) to compute a blend factor.
// If deltaTime exceeds threshold, it is clamped; otherwise deltaTime is set to 0 (no smoothing).
// For each component, if the input value <= 0.0, the previous smoothed value is retained.
// Stores per-component input, difference from previous, and the computed factor in globals.

#include <cmath> // not strictly needed, but for clarity

// Global variables (likely static in a .cpp file)
// +0x00: gSmoothThreshold (DAT_00e2e780)
// +0x04: gTimeConstant (DAT_00e2b1a4)
// +0x08: gBlendFactor (DAT_012053a8)
// +0x0C: gClampedDeltaTime (DAT_012053a4)
// +0x10: gCurrentInput[3] (DAT_0120538c, _90, _94)
// +0x1C: gPreviousSmoothed[3] (DAT_011280f0, _f4, _f8)
// +0x28: gDelta[3] (DAT_01205398, _9c, _a0)

void __fastcall analogInputProcessor(float* inputVector, float deltaTime)
{
    float fVar1;
    // Check if deltaTime exceeds threshold
    if (gSmoothThreshold <= deltaTime) {
        // Compute blend factor: timeConstant / deltaTime
        gBlendFactor = gTimeConstant / deltaTime;
    } else {
        // Clamp deltaTime to 0 (no interpolation)
        deltaTime = 0.0f;
    }
    gClampedDeltaTime = deltaTime;

    // Process first component (X)
    gCurrentInput[0] = inputVector[0];
    if (inputVector[0] <= 0.0f) {
        gCurrentInput[0] = gPreviousSmoothed[0];
    }
    fVar1 = gCurrentInput[0];
    if (deltaTime != 0.0f) {
        gDelta[0] = gCurrentInput[0] - gPreviousSmoothed[0];
        fVar1 = gPreviousSmoothed[0]; // Keep previous unchanged when smoothing active
    }
    gPreviousSmoothed[0] = fVar1;

    // Process second component (Y)
    gCurrentInput[1] = inputVector[1];
    if (inputVector[1] <= 0.0f) {
        gCurrentInput[1] = gPreviousSmoothed[1];
    }
    fVar1 = gCurrentInput[1];
    if (deltaTime != 0.0f) {
        gDelta[1] = gCurrentInput[1] - gPreviousSmoothed[1];
        fVar1 = gPreviousSmoothed[1];
    }
    gPreviousSmoothed[1] = fVar1;

    // Process third component (Z)
    gCurrentInput[2] = inputVector[2];
    if (inputVector[2] <= 0.0f) {
        gCurrentInput[2] = gPreviousSmoothed[2];
    }
    if (deltaTime != 0.0f) {
        gDelta[2] = gCurrentInput[2] - gPreviousSmoothed[2];
        // Note: No update of gPreviousSmoothed[2] when deltaTime != 0
        return;
    }
    // When deltaTime == 0, update previous to current input
    gPreviousSmoothed[2] = gCurrentInput[2];
}