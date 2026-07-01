// FUNC_NAME: PlayerController::calculateSmoothedDelta
float __thiscall PlayerController::calculateSmoothedDelta(float input, const MovementData* moveData, float deltaTime, float* outAcceleration)
{
    float speedLimit = *(float*)((int)moveData + 0x10C);
    float scaledInput = *(float*)((int)moveData + 0xFC) * input;

    // Check if the player is alive and active
    bool isAlive = *(char*)((int)this + 0x5E0) != '\0';
    bool isActive = *(char*)((int)this + 0x5E2) != '\0';
    if (!isAlive && !isActive) {
        scaledInput = 0.0f;
    }

    float desiredValue = scaledInput + *(float*)((int)moveData + 0xD4);
    float minValue = *(float*)((int)moveData + 0xD8);
    float valueA = *(float*)((int)moveData + 0xDC);
    float valueB = *(float*)((int)moveData + 0xE0);

    // Interpolate the acceleration magnitude
    float interpolatedDelta = (desiredValue - minValue) * deltaTime;
    *outAcceleration = (valueA - (valueA - valueB) * deltaTime) * speedLimit;

    // Re-evaluate after interpolation (if dead/inactive, zero everything)
    if (!isAlive && !isActive) {
        interpolatedDelta = 0.0f;
        *outAcceleration = 0.0f;
    }

    // Return the smoothed change
    return (desiredValue - interpolatedDelta) * speedLimit;
}