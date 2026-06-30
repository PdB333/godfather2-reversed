// FUN_00458a80: Entity::tryPlaySound
bool __thiscall Entity::tryPlaySound(void) {
    char soundValid;
    bool result = false;
    
    // Check if the sound threshold is met and the sound is not already playing
    if ((g_soundThreshold <= *(float *)(this + 0x158)) &&
        (*(int *)(this + 0x168) == 0)) {
        // Ensure the sound resource is valid
        soundValid = AudioSystem::isSoundValid(*(int *)(this + 0x164));
        if (soundValid != '\0') {
            float param0 = g_defaultParameter;  // +0x00e2eff4
            double param2 = 0.0;
            
            // Build and play the sound event with parameters
            AudioSystem::beginSoundEvent();
            AudioSystem::setParameterFloat(0, &param0);
            AudioSystem::setParameterDouble(2, &param2);
            AudioSystem::endSoundEvent();
            
            // If after playing the condition still holds, suppress to avoid repeats
            if ((*(float *)(this + 0x158) <= param0) &&
                ((param0 != *(float *)(this + 0x158) ||
                  (param2 <= g_doubleThreshold)))) {  // +0x00e44568
                return false;
            }
        }
        result = true;
    }
    return result;
}