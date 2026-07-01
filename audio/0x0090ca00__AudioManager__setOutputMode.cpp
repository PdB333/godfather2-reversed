// FUNC_NAME: AudioManager::setOutputMode

void __thiscall AudioManager::setOutputMode(int this, int mode)
{
    int speakerConfig;
    
    if (mode == 0) {
        speakerConfig = 1;   // Likely stereo
    } else {
        speakerConfig = 3;   // Likely 5.1 surround
    }
    AudioSystem::setSpeakerConfig(speakerConfig);
    *(int *)(this + 0x40) = mode;   // Store current output mode
    GameSettings::setInt("Audio.OutputMode", mode);  // Persist setting
    return;
}