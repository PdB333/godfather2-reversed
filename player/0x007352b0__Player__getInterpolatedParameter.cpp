// FUNC_NAME: Player::getInterpolatedParameter
float Player::getInterpolatedParameter()
{
    float fVar6 = g_globalFloat1;        // DAT_00e44598 - some global threshold or constant
    VehicleState* pVehicleState = *(VehicleState**)(this + 0x1f50); // +0x1f50 - pointer to vehicle/movement state
    float defaultEnd = g_defaultEnd;      // _DAT_00d5780c - default end value

    if (pVehicleState != nullptr) {
        VehicleData* pVehicleData = *(VehicleData**)(pVehicleState + 0x1c); // +0x1c - pointer to vehicle data or config
        float start, end;
        if (pVehicleData == nullptr || pVehicleData->type == 0x3c) { // 0x3c probably an enum for 'none' or 'default'
            start = g_defaultStart;    // _DAT_00d5780c (same as earlier? but used for start in this branch)
            end = g_defaultEnd2;       // DAT_00d5eee4
        } else {
            start = pVehicleData->startBlend;   // +0xd4
            end   = pVehicleData->endBlend;     // +0xd0
        }
        float thresholdMin = pVehicleState->thresholdMin; // +0x40
        float thresholdMax = pVehicleState->thresholdMax; // +0x4c
        float current = thresholdMin; // +0x40 (note: same as thresholdMin, likely a current value that gets overwritten later? Actually fVar3 = fVar1, so it's reused)

        float totalDuration = getMaxTime();   // FUN_0078aee0 - something like total animation/physics time
        float currentTime  = getCurrentTime();// FUN_0078ae90

        // Condition: global1 < (thresholdMin - thresholdMax) and some time delta > g_timeDeltaThreshold
        if (fVar6 < (thresholdMin - thresholdMax) && g_timeDeltaThreshold < (totalDuration - currentTime)) {
            float newCurrentTime = getCurrentTime(); // get current time again (used as numerator)
            // Linear interpolation: t = (current - newCurrentTime) / (totalDuration - currentTime)
            // Then result = t * (end - start) + start
            float t = (current - newCurrentTime) / (totalDuration - currentTime);
            return t * (end - start) + start;
        }
    }

    return defaultEnd; // from beginning
}