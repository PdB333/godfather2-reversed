// FUNC_NAME: AudioManager::setEffectsVolume
void __thiscall AudioManager::setEffectsVolume(int this, float volume)
{
    // Store volume in member variable at offset +0x1c
    *(float *)(this + 0x1c) = volume;
    // Apply to global audio mixer object
    AudioMixer::setVolume(&gAudioMixer, volume);
    // Apply to the "Audio.Effects" category
    AudioManager::setCategoryVolume("Audio.Effects", volume);
    return;
}