// FUN_00466280: EARSVehicleController::limitAndDampVector
void __thiscall EARSVehicleController::limitAndDampVector(float param_2)
{
    // Note: ESI and EDI are expected to point to two float components (x and y) of a 2D vector.
    // They are not declared as parameters; they are set by the caller before calling this method.
    float* componentX = unaff_ESI; // from register ESI
    float* componentY = unaff_EDI; // from register EDI

    float* storedParam = (float*)(param_1 + 0x16b0); // optional stored parameter override

    // Global constants
    const float& defaultParamOverride = DAT_00e2eff4; // sentinel value
    const float& maxMagnitude = DAT_00e2b1a4;       // maximum allowed magnitude

    // If param_2 equals the sentinel, use the stored value instead
    if (param_2 == defaultParamOverride) {
        param_2 = *storedParam;
    }

    float x = *componentX;
    float y = *componentY;
    float magnitude = sqrtf(x * x + y * y);

    // Clamp magnitude to [0, maxMagnitude]
    if (magnitude > 0.0f && magnitude > maxMagnitude) {
        magnitude = maxMagnitude;
    } else if (magnitude < 0.0f) {
        magnitude = 0.0f;
    }

    // The following calls are likely floating-point control/state adjustments (e.g., rounding or precision).
    // They appear to be no-ops or context switches for the x87 FPU.
    FUN_00b9a9fa(); // possibly _control87 or similar
    FUN_00b9af10();

    // Compute scaling factor: (magnitude * (maxMagnitude - param_2) + magnitude * param_2) = magnitude * maxMagnitude
    // Actually the decompiled expression is:
    // fVar1 = (float)dVar3 * (maxMagnitude - param_2) + magnitude * param_2;
    // where dVar3 = (double)magnitude, so (float)dVar3 = magnitude, thus:
    // fVar1 = magnitude * (maxMagnitude - param_2) + magnitude * param_2 = magnitude * maxMagnitude
    float scalingFactor = magnitude * maxMagnitude;

    // Multiply original x and y components by the scaling factor
    double originalX = (double)x;
    FUN_00b99e20(); // another FPU control call
    *componentY = (float)(originalX * (double)scalingFactor);

    originalX = (double)x;
    FUN_00b99fcb(); // final FPU control call
    *componentX = (float)(originalX * (double)scalingFactor);

    // Note: After this operation, both components are scaled equally, so the vector direction remains unchanged,
    // but the magnitude becomes: sqrt( (x*scale)^2 + (y*scale)^2 ) = scale * originalMagnitude = (magnitude * maxMagnitude) * originalMagnitude.
    // This seems incorrect or the decompilation may have misrepresented the true intent (perhaps the calls do something else like sin/cos).
}
// +0x16b0: stored parameter override (float)
// DAT_00e2eff4: sentinel value indicating override request
// DAT_00e2b1a4: global maximum magnitude for clamping (float)