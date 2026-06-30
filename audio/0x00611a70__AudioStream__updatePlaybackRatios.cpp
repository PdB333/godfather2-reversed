// FUNC_NAME: AudioStream::updatePlaybackRatios
void AudioStream::updatePlaybackRatios(void)
{
    float* ratio1;
    uint streamIndex;
    int state;
    float baseRate;
    StreamInfoEntry* entry;
    
    baseRate = DAT_00e2b1a4; // Global base playback rate constant
    streamIndex = *(uint*)(this + 0x100); // Current stream index
    if (streamIndex < 0x1000) {
        entry = &DAT_011a0f28[streamIndex * 0x38]; // Table of 0x38-byte stream info entries
    } else {
        entry = nullptr;
    }
    ratio1 = (float*)(this + 0x124); // First playback ratio (e.g., pitch)
    *ratio1 = baseRate / (float)*(ushort*)(entry + 2); // Divide by sample rate/period at entry offset 2

    if (streamIndex < 0x1000) {
        entry = &DAT_011a0f28[streamIndex * 0x38];
    } else {
        entry = nullptr;
    }
    state = *(int*)(this + 0x138); // Some state indicator
    *(float*)(this + 0x128) = baseRate / (float)*(ushort*)(entry + 4); // Second playback ratio (e.g., secondary pitch)

    if (((state == 4) || (state == 5)) || (state == 0xe)) {
        // If state is one of these and flag at +0x13c is 1, zero the corresponding ratio
        if (*(int*)(this + 0x13c) == 1) {
            *(float*)(this + 0x128) = 0.0f;
        } else {
            *(float*)(this + 0x124) = 0.0f;
        }
    }
    if (*(int*)(this + 0x11c) != 0) {
        applyPlaybackRatio(*(uint*)(this + 0x14), *(int*)(this + 0x11c), ratio1);
    }
    if (*(int*)(this + 0x120) != 0) {
        applyPlaybackRatio(*(uint*)(this + 0x10), *(int*)(this + 0x120), ratio1);
    }
}