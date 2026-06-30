// FUNC_NAME: BaseVehicle::computeAccelerationForce
// Address: 0x006c36e0
// Role: Computes the acceleration force for a vehicle based on current speed, target speed, and input (accelerator/brake).
// Uses a smooth interpolation toward target speed and applies different gains for acceleration versus braking.

// Assumed class BaseVehicle with relevant fields:
// +0xe8: Pointer to a physics body or some derived state (maybe a physics component)
// +0x2e8: Current vehicle speed (float)
// +0x2cc: Vehicle mass or inertia factor (float)

// Global tuning constants (likely from data section):
// _DAT_00e50f78: Smoothing factor for speed interpolation (0..1)
// _DAT_00e50f74: Scale factor for acceleration calculation (inverse of something)
// DAT_00e50f64: Acceleration gain coefficient (positive acceleration)
// _DAT_00e50f68: Braking gain coefficient multiplier
// DAT_00e50f6c: Linear braking coefficient
// DAT_00e50f70: Quadratic braking coefficient (drag)
// _DAT_00e50f54, _DAT_00e50f58, _DAT_00e50f5c, _DAT_00e50f60: Parameters for final clamping/curve function

float __thiscall BaseVehicle::computeAccelerationForce(int this, float acceleratorInput, float brakeInput)
{
    int physicsBodyPtr; // pointer to physics component or derived state
    float targetSpeed; // desired speed from some sub-function
    float currentSpeed; // current speed from this+0x2e8
    float smoothedSpeed; // interpolated speed
    float rawAcceleration; // acceleration before gain calculation
    float effectiveNetInput; // net input (brake - accelerator) but used in sign-based gain

    // Determine physics body pointer: if this+0xe8 is non-zero, subtract 0x48 to get parent object or base pointer
    if (*(int *)(this + 0xe8) == 0) {
        physicsBodyPtr = 0;
    } else {
        physicsBodyPtr = *(int *)(this + 0xe8) - 0x48;
    }

    // Get target speed from some other function (e.g., desired speed based on input)
    targetSpeed = (float) FUN_006c93c0(physicsBodyPtr); // assume returns float

    // Read current speed from this object
    currentSpeed = *(float *)(this + 0x2e8);

    // Smoothly interpolate current speed toward target speed using smoothing factor
    smoothedSpeed = (targetSpeed - currentSpeed) * _DAT_00e50f78 + currentSpeed;

    // Update stored speed
    *(float *)(this + 0x2e8) = smoothedSpeed;

    // Compute raw acceleration = change in speed / (mass * scale factor)
    rawAcceleration = (smoothedSpeed - currentSpeed) / (*(float *)(this + 0x2cc) * _DAT_00e50f74);

    // Compute effective net input: brakeInput - acceleratorInput? Actually param_3 - param_2, param_2 likely accelerator, param_3 likely brake
    effectiveNetInput = brakeInput - acceleratorInput;

    // Apply different gain depending on sign of rawAcceleration (accelerating vs braking/decelerating)
    if (rawAcceleration >= 0.0f) {
        // Accelerating: use linear gain
        rawAcceleration = DAT_00e50f64 * effectiveNetInput * rawAcceleration;
    } else {
        // Braking/decelerating: use quadratic drag model
        rawAcceleration = (DAT_00e50f6c * rawAcceleration - DAT_00e50f70 * rawAcceleration * rawAcceleration) * _DAT_00e50f68 * effectiveNetInput;
    }

    // Apply final curve/clamping function to the smoothed speed (e.g., limit, friction)
    float speedClamped = (float) FUN_006c91c0(smoothedSpeed, _DAT_00e50f54, _DAT_00e50f58, _DAT_00e50f5c, _DAT_00e50f60);

    // Return final acceleration force scaled by the clamped speed factor
    return speedClamped * rawAcceleration;
}