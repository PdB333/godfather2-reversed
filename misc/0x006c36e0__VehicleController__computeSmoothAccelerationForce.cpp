// FUNC_NAME: VehicleController::computeSmoothAccelerationForce
// Address: 0x006c36e0
// Role: Computes a smoothed acceleration/force for a vehicle control axis.
// Uses an input object at offset +0xe8 (likely a controller/input device).
// Applies exponential smoothing, then computes a force based on the rate of change,
// with different coefficients for positive (acceleration) and negative (braking/drag) directions.
// Final output is shaped by a response curve (deadzone/power curve) and scaled by input range.

long double VehicleController::computeSmoothAccelerationForce(float minInput, float maxInput)
{
    // Get pointer to input source at offset +0xe8
    // If null, treat as zero (call FUN_006c93c0 on null/zero)
    int inputObj;
    if (*(int*)(this + 0xe8) == 0) {
        inputObj = 0;
    } else {
        inputObj = *(int*)(this + 0xe8) - 0x48; // adjust for base class offset (vtable/this adjustment)
    }

    // Get raw target value from input source (e.g., joystick axis)
    float rawInput = (float)FUN_006c93c0(inputObj);

    // Exponential smoothing of the target value
    // +0x2e8: current smoothed value
    float currentSmoothed = *(float*)(this + 0x2e8);
    float smoothingFactor = _DAT_00e50f78; // e.g., 0.05 (smoothing constant)
    float newSmoothed = (rawInput - currentSmoothed) * smoothingFactor + currentSmoothed;
    *(float*)(this + 0x2e8) = newSmoothed;

    // Compute normalized rate of change (derivative-like term)
    // +0x2cc: max speed or max response limit
    float maxResponse = *(float*)(this + 0x2cc);
    float normDiff = (newSmoothed - currentSmoothed) / (maxResponse * _DAT_00e50f74);

    // Compute force based on direction (positive=accelerate, negative=brake/drag)
    float force;
    if (normDiff >= 0.0f) {
        // Positive acceleration (applying throttle/steering)
        force = _DAT_00e50f64 * (maxInput - minInput) * normDiff;
    } else {
        // Negative acceleration (braking/drag) - quadratic drag model
        // DAT_00e50f6c: linear drag coefficient, DAT_00e50f70: quadratic drag coefficient
        // DAT_00e50f68: overall drag multiplier
        float drag = _DAT_00e50f6c * normDiff - _DAT_00e50f70 * normDiff * normDiff;
        force = drag * _DAT_00e50f68 * (maxInput - minInput);
    }

    // Apply a response curve/deadzone function to the smoothed target value
    // DAT_00e50f54, DAT_00e50f58, DAT_00e50f5c, DAT_00e50f60: curve parameters
    long double responseCurve = FUN_006c91c0(newSmoothed,
                                            _DAT_00e50f54, _DAT_00e50f58,
                                            _DAT_00e50f5c, _DAT_00e50f60);

    // Return scaled force (80-bit extended precision)
    return responseCurve * (long double)force;
}