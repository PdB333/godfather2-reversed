// FUNC_NAME: TargetingManager::isEntityInRange
bool __fastcall TargetingManager::isEntityInRange(int entityPtr) {
    // +0x2c: likely entity's distance/squared distance from something (e.g., player)
    float entityDistance = *(float*)(entityPtr + 0x2c);

    // Global maximum detection range (e.g., g_maxDetectionRange)
    if (g_maxDetectionRange <= entityDistance) {
        // Global full-scale value (e.g., max sensor range) minus entity distance
        float diff = g_sensorMaxRange - entityDistance;

        // Mask to clear sign bit or handle truncation; often 0x7FFFFFFF for absolute value
        uint32_t masked = (uint32_t)diff & g_rangeMask;
        
        // Global minimum distance threshold (e.g., g_minRangeThreshold)
        if ((float)masked < g_minRangeThreshold) {
            return true;
        }
    }
    return false;
}