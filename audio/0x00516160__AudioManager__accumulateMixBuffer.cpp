// FUNC_NAME: AudioManager::accumulateMixBuffer
void AudioManager::accumulateMixBuffer(void)
{
    // This function accumulates audio samples from a source buffer into a global mix buffer.
    // The source buffer is pointed to by in_EAX (a float array of at least 6 elements).
    // The global mix buffer is at 0x012066b0 (4 floats for left/right channels?).
    // The global peak value is at 0x012066c4, and a flag/state at 0x012066c0.
    // DAT_00e2b1a4 is a gain/volume factor.

    // Accumulate first 4 samples (likely stereo interleaved or 4-channel) with gain
    _DAT_012066b0 = DAT_00e2b1a4 * *in_EAX + _DAT_012066b0;       // +0x00: mix buffer sample 0
    _DAT_012066b4 = DAT_00e2b1a4 * in_EAX[1] + _DAT_012066b4;     // +0x04: mix buffer sample 1
    _DAT_012066b8 = DAT_00e2b1a4 * in_EAX[2] + _DAT_012066b8;     // +0x08: mix buffer sample 2
    _DAT_012066bc = DAT_00e2b1a4 * in_EAX[3] + _DAT_012066bc;     // +0x0C: mix buffer sample 3

    // Track peak value (in_EAX[5] is the absolute peak of the source block)
    if (DAT_012066c4 < in_EAX[5]) {                                // +0x14: peak tracker
        DAT_012066c4 = in_EAX[5];                                  // update peak
        DAT_012066c0 = DAT_012066c0 | (uint)in_EAX[4];            // +0x10: flag/state, OR with source flags
        return;
    }
    DAT_012066c0 = DAT_012066c0 | (uint)in_EAX[4];                // always OR flags even if no peak update
    return;
}