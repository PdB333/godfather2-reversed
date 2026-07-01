// FUNC_NAME: OptionsManager::loadSettings
void __thiscall OptionsManager::loadSettings(void) {
    char subtitlesEnabled;
    int audioOutputMode;
    float musicVolume;
    float effectsVolume;
    float xSensitivity;
    float ySensitivity;
    float clampedSensitivity;
    float minSensitivity;
    float maxSensitivity;
    int mouseSensitivity;
    int mouseAutoTarget;
    int vsyncEnabled;
    unsigned int vibeControllerIndex;

    // Read subtitles setting
    subtitlesEnabled = getConfigBool("Audio.Subtitles", false);
    if (subtitlesEnabled == 0) {
        // Clear bit 0 (subtitles flag)
        m_flags = m_flags & ~0x01;
    } else {
        m_flags = m_flags | 0x01;
    }
    setConfigBool("Audio.Subtitles", subtitlesEnabled);

    // Read vibration setting
    vibEnabled = getConfigBool("Controls.Vibration", true);
    // Apply vibration to the first controller (index from global)
    vibeControllerIndex = *(unsigned char*)(DAT_01129814 + 0x14); // +0x14 offset of controller count? or active controller?
    if (vibeControllerIndex < 16) {
        setControllerVibration(vibeControllerIndex, vibEnabled == 0);
    }
    if (vibEnabled == 0) {
        m_flags = m_flags & ~0x02; // Clear bit 1 (vibration flag)
    } else {
        m_flags = m_flags | 0x02;
    }
    setConfigBool("Controls.Vibration", vibEnabled);

    // Read mouse invert
    mouseInvert = getConfigBool("Mouse.Invert", false);
    DAT_0112a7a4 = mouseInvert; // Global invert flag
    if (mouseInvert == 0) {
        m_flags = m_flags & ~0x08; // Clear bit 3
    } else {
        m_flags = m_flags | 0x08;
    }
    setConfigBool("Mouse.Invert", mouseInvert);

    // Read music volume
    musicVolume = (float)getConfigFloat("Audio.Music", 1.0f);
    audioSetVolume("MUSIC", musicVolume);
    m_musicVolume = musicVolume;
    setConfigFloat("Audio.Music", musicVolume);

    // Read effects volume
    effectsVolume = (float)getConfigFloat("Audio.Effects", 1.0f);
    audioSetVolume("SFX", effectsVolume);
    m_effectsVolume = effectsVolume;
    setConfigFloat("Audio.Effects", effectsVolume);

    // Read audio output mode
    audioOutputMode = getConfigInt("Audio.OutputMode", 0);
    if (audioOutputMode == 0) {
        setAudioOutputMode(1); // Stereo?
    } else {
        setAudioOutputMode(3); // Surround?
    }
    m_audioOutputMode = audioOutputMode;
    setConfigInt("Audio.OutputMode", audioOutputMode);

    // Read gamma
    float gamma = (float)getConfigFloat("Window.Gamma", 0.0f);
    setGamma(gamma);

    // Read brightness
    int brightness = getConfigInt("Window.Bright", 0);
    setBrightness(brightness);

    // Read X sensitivity with clamping
    xSensitivity = (float)getConfigFloat("Controls.XSensitivity", 1.0f);
    minSensitivity = DAT_00d5ef88; // Minimum sensitivity constant
    maxSensitivity = DAT_00d5eee4; // Maximum sensitivity constant
    if (xSensitivity < minSensitivity || xSensitivity > maxSensitivity) {
        xSensitivity = (xSensitivity < minSensitivity) ? minSensitivity : maxSensitivity;
    }
    _DAT_00e50fb8 = xSensitivity;
    m_xSensitivity = xSensitivity;
    setConfigFloat("Controls.XSensitivity", xSensitivity);

    // Read Y sensitivity with clamping
    ySensitivity = (float)getConfigFloat("Controls.YSensitivity", 1.0f);
    if (ySensitivity < minSensitivity || ySensitivity > maxSensitivity) {
        ySensitivity = (ySensitivity < minSensitivity) ? minSensitivity : maxSensitivity;
    }
    _DAT_00e50fbc = ySensitivity;
    m_ySensitivity = ySensitivity;
    setConfigFloat("Controls.YSensitivity", ySensitivity);

    // Read mouse sensitivity
    mouseSensitivity = getConfigInt("Mouse.Sensitivity", 3);
    setMouseSensitivity(mouseSensitivity);

    // Read auto target
    mouseAutoTarget = getConfigInt("Mouse.AutoTarget", 0);
    m_mouseAutoTarget = mouseAutoTarget;
    setConfigInt("Mouse.AutoTarget", mouseAutoTarget);

    // Read VSync
    vsyncEnabled = getConfigInt("Window.VSync", 0);
    m_vsyncEnabled = vsyncEnabled;
    setVSync(vsyncEnabled != 0);
    setConfigInt("Window.VSync", vsyncEnabled);
}