// FUNC_NAME: audioMixerUpdateState

void audioMixerUpdateState(undefined4 param_1, uint mixerData) {
    // Global state for audio mixer system
    // Structure offsets:
    // +0x000: channelVolumes[8] (8 floats)  [0x012191e0..0x012191fc]
    // +0x020: band1, band2, band3 (3 floats) [0x01219200,0x04,0x08]
    // +0x02c: intParam1 (int) [0x0121920c]
    // +0x030: floatParam1, floatParam2, floatParam3 (3 floats) [0x01219210,0x14,0x18]
    // +0x03c: intParam2 (int) [0x0121921c]
    // +0x040: floatParam4 (float) [0x01219220]
    // +0x044: defaultTimeConstant1 (float) [0x01219224]
    // +0x048: defaultTimeConstant2 (float) [0x01219228]
    // +0x04c: floatParam5 (float) [0x0121922c]
    // +0x050: modeFlag (int) [0x01219230]
    // +0x054: masterVolume (float) [0x01219240]
    extern float s_masterVolume;          // DAT_01219240
    extern float s_previousMasterVolume;  // DAT_00e2b05c
    extern float s_threshold;             // DAT_00e2af44
    extern float s_targetVolume;          // DAT_00e2b1a4
    extern float s_channelVolumes[8];     // DAT_012191e0
    extern float s_band1, s_band2, s_band3;          // 0x01219200,0x04,0x08
    extern int   s_intParam1;                         // 0x0121920c
    extern float s_floatParam1, s_floatParam2, s_floatParam3; // 0x01219210,0x14,0x18
    extern int   s_intParam2;                         // 0x0121921c
    extern float s_floatParam4;                       // 0x01219220
    extern float s_defaultTimeConstant1;              // 0x01219224
    extern float s_defaultTimeConstant2;              // 0x01219228
    extern float s_floatParam5;                       // 0x0121922c
    extern int   s_modeFlag;                          // 0x01219230
    extern float s_defaultTimeConstant;               // DAT_00e2eb58

    bool bVar1;
    float fVar2;

    // Check if master volume changed and thresholds exceeded
    if (s_masterVolume != s_previousMasterVolume &&
        ((s_threshold <= s_floatParam4 &&
          ((s_threshold <= s_band1 || s_threshold <= s_band2 || s_threshold <= s_band3))) ||
         (s_threshold <= s_floatParam5 &&
          ((s_threshold <= s_floatParam1 || s_threshold <= s_floatParam2 || s_threshold <= s_floatParam3))))) {
        // Compute scale factor from target to master volume
        fVar2 = s_targetVolume / s_masterVolume;

        // Scale all channel volumes
        for (int i = 0; i < 8; i++) {
            s_channelVolumes[i] *= fVar2;
        }

        // Process the mixer bank
        bVar1 = processMixerBank(s_channelVolumes, s_modeFlag, mixerData);

        if (!bVar1) {
            // Reset thresholds to target volume
            s_band1 = s_targetVolume;
            s_band2 = s_targetVolume;
            s_band3 = s_targetVolume;

            // Zero out channel volumes
            for (int i = 0; i < 8; i++) {
                s_channelVolumes[i] = 0.0f;
            }

            // Reset other parameters to zero
            s_intParam1 = 0;
            s_intParam2 = 0;
            s_floatParam1 = 0.0f;
            s_floatParam2 = 0.0f;
            s_floatParam3 = 0.0f;
            s_floatParam4 = 0.0f;
            s_floatParam5 = 0.0f;

            // Reset time constants to default
            s_defaultTimeConstant1 = s_defaultTimeConstant;
            s_defaultTimeConstant2 = s_defaultTimeConstant;

            // Reset mode flag and master volume
            s_modeFlag = 0;
            s_masterVolume = 0.0f;
        }
    }
}