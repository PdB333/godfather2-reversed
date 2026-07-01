// FUNC_NAME: Weapon::updateTimer
void __thiscall Weapon::updateTimer(float deltaTime) {
    // Accumulate elapsed time (+0x14)
    this->elapsedTime += deltaTime;

    // Check if elapsed time exceeds the threshold (+0x10) and the global max is smaller than threshold
    if (this->thresholdTime <= this->elapsedTime && g_globalMaxThreshold < this->thresholdTime) {
        // Play associated sound/effect using global sound ID
        SoundBuffer soundBuffer;
        soundBuffer.soundId = g_soundId;    // DAT_0112f9c0
        soundBuffer.param1 = 0;
        soundBuffer.param2 = 0;
        playSound(&soundBuffer, 0);         // FUN_00408a00

        // Fire multiple shot sounds (presumably weapon burst)
        playShotSound();                    // FUN_008d5dc0
        playShotSound();
        playShotSound();
        playShotSound();

        // Reset state
        this->stateFlags = 0;               // +0x78, e.g., "isFiring" flag
        this->elapsedTime = 0.0f;           // Reset timer
    }
}