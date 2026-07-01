// FUNC_NAME: HavokWheeledVehicle::updateSteeringSmooth
// Address: 0x007af8e0
// Role: Reads combined left/right analog input, computes target steering angle, and smoothly updates current steering angle with a maximum delta per frame.

void HavokWheeledVehicle::updateSteeringSmooth()
{
    // Get pointer to physics state (vehPhysics or similar) at this+0x58
    void* vehPhysics = *(void**)(this + 0x58);

    // Uninitialized locals used for axis readings
    int axis0Raw;      // local_10 - unused after reading
    float axis0Value;  // local_c - first axis (e.g., stick X)
    float axis1Value;  // local_4  - second axis (e.g., stick Y)

    // Read two controller axes (likely left analog X and Y, or left/right triggers)
    // FUN_0079eab0:  param0=0 -> axis0,  param0=1 -> axis1
    // The last three parameters are probably dead zone, scale, scale2 (all same global)
    readControllerAxis(0, &axis0Raw, &axis0Value, 0, 0, gDeadZone, gDeadZone, gDeadZone);
    readControllerAxis(1, (int*)&axis0Value + 4, &axis1Value, 0, 0, gDeadZone, gDeadZone, gDeadZone);
    // Note: The second call stores its output in axis0Value+4 (overwriting part of axis0Raw?) but axis0Raw is unused.
    // So axis0Value holds the first axis, axis1Value the second.

    // Combine axes and apply sensitivity and dead zone scaling
    float combinedInput = axis1Value + axis0Value;
    float targetValue = combinedInput * gInputSensitivity * gDeadZone;

    // Clamp target to allowed range (defined by global min/max)
    float minClamp = gMinSteering;   // DAT_00d6bbf8
    float maxClamp = gMaxSteering;   // DAT_00e446dc
    if (targetValue > maxClamp || targetValue < minClamp) {
        targetValue = (targetValue > maxClamp) ? maxClamp : minClamp;
    }

    // Get current steering value from physics state (+0x2894)
    float currentSteering = *(float*)(vehPhysics + 0x2894);
    // Get max allowed change per frame from physics state (+0x1fbc)
    float maxSteeringDelta = *(float*)(vehPhysics + 0x1fbc);

    // Apply gradual approach with delta limiting
    if (currentSteering <= targetValue) {
        if (targetValue <= currentSteering) {
            // Already exactly at target – nothing to do
            return;
        }
        // Need to increase steering
        if (maxSteeringDelta < targetValue - currentSteering) {
            // Can't reach target in one step, move by max delta from current
            setSteeringAngle(currentSteering + maxSteeringDelta);
            return;
        }
    } else {
        // Need to decrease steering
        if (maxSteeringDelta < currentSteering - targetValue) {
            setSteeringAngle(currentSteering - maxSteeringDelta);
            return;
        }
    }
    // Within delta range, set directly to target
    setSteeringAngle(targetValue);
}