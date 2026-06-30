// FUNC_NAME: AudioManager::updateFade
void AudioManager::updateFade(uint fadeDirection)
{
    // Get current fade factor (0.0 to 1.0 range)
    float fadeFactor = GetAudioFadeFactor();   // FUN_00518510

    // Shift fade targets:
    // +0x00: previous target volume (DAT_012192bc) <- current target (DAT_012192dc)
    // +0x04: current target volume (DAT_012192dc) <- volatile target (DAT_00e2b1a4)
    _DAT_012192bc = DAT_012192dc;
    DAT_012192dc = DAT_00e2b1a4;

    // Apply fade: channelArray[0] (DAT_012192b0), channelIndex (0x012192d8),
    // masterVolume=1.0f, flags=0, fadeDirection, fadeFactor, param6, param7
    ApplyAudioChannelFade(&DAT_012192b0, _DAT_012192d8, 1.0f, 0,
                          fadeDirection, fadeFactor, DAT_012192e0, DAT_012192e4);
}