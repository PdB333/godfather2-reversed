// FUNC_NAME: BaseVehicle::computeEngineForce
float BaseVehicle::computeEngineForce(float throttle, float currentSpeed) {
    // +0x1A8: baseEngineForce (float)
    float result = *(float*)((uintptr_t)this + 0x1A8);
    
    // Apply reverse scaling: if throttle negative (reverse) and current speed below threshold
    if (throttle < 0.0f && currentSpeed <= g_reverseSpeedThreshold) {
        result *= g_reverseEngineForceMultiplier;
    }
    
    return result;
}