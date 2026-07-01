// FUNC_NAME: BaseVehicle::updateWheelTargetSpeed
void __thiscall BaseVehicle::updateWheelTargetSpeed(int thisPtr, int inputThrottle, int wheelIndex, int state)
{
    const float INPUT_CONVERSION_CONST = DAT_00e44578; // Conversion constant for negative input (likely 65536.0f)
    const float THRESHOLD_MULTIPLIER = DAT_00d5efb8;   // Threshold multiplier for grip detection
    const float SPEED_REDUCTION_MULTIPLIER = DAT_00d58cbc; // Multiplier for speed reduction based on charge

    float fThrottle = (float)inputThrottle;
    if (inputThrottle < 0) {
        fThrottle += INPUT_CONVERSION_CONST; // Convert signed input to unsigned range
    }

    // Get pointer to physics data (at +0x58 from this)
    int physicsData = *(int*)(thisPtr + 0x58);

    // Check if current grip or traction at wheel wheelIndex is below threshold
    // Array at physicsData+0x3080 stores per-wheel grip values
    if (*(float*)(physicsData + 0x3080 + wheelIndex * 4) < fThrottle * THRESHOLD_MULTIPLIER) {
        // Reset charge counter for this wheel (array at +0x306c)
        *(int*)(physicsData + 0x306c + wheelIndex * 4) = 0;
    }

    // Read base max speed from physics data
    float baseSpeed = *(float*)(physicsData + 0x2124); // Max speed
    *(float*)(thisPtr + 0x19c) = baseSpeed;            // Default target speed

    // Get the charge count for this wheel
    uint charge = *(uint*)(physicsData + 0x306c + wheelIndex * 4);

    if ((charge > 1) && (state != 3) && (state != 4)) {
        int reduced = charge - 1;
        float fReduced = (float)reduced;
        if (reduced < 0) {
            fReduced += INPUT_CONVERSION_CONST;
        }
        // Speed reduction scales with charge
        float reduction = fReduced * baseSpeed * SPEED_REDUCTION_MULTIPLIER;
        float newTarget = baseSpeed - reduction;

        // Minimum speed clamp (array at +0x200c stores min speed ratio)
        float minSpeed = *(float*)(physicsData + 0x200c) * baseSpeed;
        if (newTarget < minSpeed) {
            newTarget = minSpeed;
        }

        *(float*)(thisPtr + 0x19c) = newTarget;
    }

    return;
}