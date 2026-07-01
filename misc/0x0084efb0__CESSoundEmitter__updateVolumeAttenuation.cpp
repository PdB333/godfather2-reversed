// FUNC_NAME: CESSoundEmitter::updateVolumeAttenuation
void __thiscall CESSoundEmitter::updateVolumeAttenuation(CESSoundEmitter* this, uint32_t soundHandle) {
    // Retrieve listener position from audio system (likely AudioListenerManager)
    float* listenerPos = reinterpret_cast<float*>(FUN_00471610());
    // Vector from sound source to listener
    float dx = listenerPos[0x30/4] - this->position.x;       // +0x30 is listenerX
    float dy = listenerPos[0x34/4] - this->position.y;       // +0x34 is listenerY
    float dz = listenerPos[0x38/4] - this->position.z;       // +0x38 is listenerZ
    float distance = sqrtf(dx*dx + dy*dy + dz*dz);
    
    // Global constants (likely 1.0, rolloff coefficient, threshold)
    const float kMaxFactor = _DAT_00d5780c;                  // ~1.0
    const float kRolloffCoeff = DAT_00d5eee4;                // empirical
    const float kVolumeThreshold = DAT_00d5ef84;             // minimum volume to play
    
    // Calculate distance factor with quadratic rolloff
    float factor = kMaxFactor;
    if (this->minDistance <= distance) {                     // +0x24 = minDist
        float range = this->maxDistance - this->minDistance; // +0x28 = maxDist
        if (range > 0.0f) {
            float t = (distance - this->minDistance) / range;
            if (t < 0.0f) t = 0.0f;
            if (t > kMaxFactor) t = kMaxFactor;
            // Quadratic rolloff: factor = 1 - (c*t - t^2)
            factor = kMaxFactor - (t * kRolloffCoeff - t * t);
        }
    }
    
    // Apply base volume scaling
    float finalVolume = this->baseVolume * factor;            // +0x20 = baseVolume (linear?)
    
    if (finalVolume > kVolumeThreshold) {
        FUN_0084eec0(soundHandle, finalVolume);
    }
    return;
}