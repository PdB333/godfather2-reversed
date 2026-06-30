// FUNC_NAME: AudioManager::setRadioState
// Function address: 0x537c40
// Purpose: Toggle radio audio state based on player's radio status (on/off).
// Uses global AudioSystem instance (DAT_0121a390) and audio settings block (DAT_0121b63c).
// Sets an integer parameter at offset 0x1c, then applies a sound environment preset
// from either DAT_011280d0 (radio on) or DAT_00e2e770 (radio off) via offset 0x2c.

void AudioManager::setRadioState(char isRadioOn)
{
    // Retrieve global audio system and settings pointers
    AudioSystem* audioSys = reinterpret_cast<AudioSystem*>(DAT_0121a390);
    AudioSettings* settings = reinterpret_cast<AudioSettings*>(DAT_0121b63c);

    // Set audio parameter at offset +0x1c (e.g., radio volume or toggle flag)
    FUN_0060b020(audioSys, *(int32_t*)((uint8_t*)settings + 0x1c));

    // Select sound environment data based on radio state
    uint8_t* soundEnvData = (isRadioOn != 0) ? &DAT_011280d0 : &DAT_00e2e770;
    // Apply sound environment preset at offset +0x2c (e.g., reverb or filter)
    FUN_0060add0(audioSys, *(int32_t*)((uint8_t*)settings + 0x2c), soundEnvData);
}