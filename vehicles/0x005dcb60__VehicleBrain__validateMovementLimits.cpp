// FUNC_NAME: VehicleBrain::validateMovementLimits
// Address: 0x005dcb60
// Role: Validates that the current speed and a derived steering/speed value are within acceptable ranges.

bool __thiscall VehicleBrain::validateMovementLimits(float *this, int conditionId, void *inputData)
{
    // Check if a condition based on the ID is met (e.g., engine on, not braking?)
    if (!CallIsConditionMet(conditionId)) {
        return false;
    }

    float computedValue; // Output: e.g., steering angle or desired speed (set by ComputeSteeringParameter)
    // Compute a derived parameter from inputData, storing result in computedValue
    ComputeSteeringParameter(inputData, &computedValue);

    // *this likely stores the vehicle's current speed (or throttle)
    // computedValue might be steering angle or target speed
    // DAT_00e2b1a4 is a global maximum speed/angle constant (e.g., 100.0f)
    if ((computedValue >= 0.0f && computedValue <= DAT_00e2b1a4) && (*this >= 0.0f)) {
        return true;
    }
    return false;
}