// FUNC_NAME: EARS::AudioMixer::processMixerChannel
float __thiscall AudioMixer::processMixerChannel(AudioMixer *this, int mode, float inputLevel, AudioBuffer *buffer)
{
    float *samplePtr;
    uint *channelState;
    int count;
    int i;
    int channelIndex;
    float accumulatedGain;
    float baseGain;
    float sampleValue;

    // Step 1: Compute initial gain via base processing function
    float gainBase = (float)AudioProcessor::computeGain(inputLevel, 0, buffer);

    float gain = gainBase;
    if (mode == 2) {
        // Mode 2: add master volume offset from global audio config (DAT_0112f938 + 0xB8)
        gain += AudioMixer::s_masterVolumeOffset; // *(float *)(DAT_0112f938 + 0xb8)

        if (buffer != NULL && buffer->count != 0) {
            // Compute per-sample gain based on buffer length
            float countFloat = (float)buffer->count;
            if (buffer->count < 0) {
                countFloat += 4294967296.0f; // Convert signed negative count to unsigned float (DAT_00e44578)
            }
            // Base gain divided by sample count provides per-sample scaling
            inputLevel = AudioMixer::s_masterVolumeOffset / countFloat;
        }

        // Check if this mixer is of a specific type (class ID 0x637b907)
        if (*(int *)(this + 0x54) == 0x637b907) {
            // Loop over 7 global channel states (stride 0x24, total 0xFC)
            channelIndex = 0;
            accumulatedGain = gain;
            do {
                // Each channel state entry is at DAT_0112989c + 0x18 + channelIndex
                channelState = (uint *)(DAT_0112989c + 0x18 + channelIndex);
                if ((channelState != NULL) && 
                    // Check bit 1 of first dword (mask 0x4? Actually (*channelState >> 2) & 1)
                    ((*channelState >> 2 & 1) != 0) &&
                    // Additional condition via helper function
                    (AudioMixer::isChannelActive() != 0) &&
                    // Check bit 2 (0x4) at offset +0x10 (channelState[4])
                    ((channelState[4] & 4) != 0)) {
                    // Channel is active: accumulate gain for this channel
                    accumulatedGain += AudioMixer::s_masterVolumeOffset;
                    if (buffer != NULL) {
                        count = buffer->count;
                        if (count != 0) {
                            float countFloat2 = (float)count;
                            if (count < 0) {
                                countFloat2 += 4294967296.0f;
                            }
                            // Add per-sample scaling factor
                            inputLevel += AudioMixer::s_masterVolumeOffset / countFloat2;
                        }
                    }
                }
                channelIndex += 0x24;
                gain = accumulatedGain;
            } while (channelIndex < 0xFC); // 0xFC / 0x24 = 7 channels
            gain = accumulatedGain; // Final gain after channel looping
        }
    }

    // Step 2: Apply final volume and sample-level mixing from this mixer instance
    float mixVolume = *(float *)(this + 0x160); // Mixer-specific volume factor
    if (buffer != NULL && buffer->count > 0) {
        // Modify each sample in the buffer: newSample = (inputLevel + oldSample) * mixVolume
        for (uint i = 0; i < (uint)buffer->count; i++) {
            samplePtr = (float *)(buffer->buffer + i);
            *samplePtr = (inputLevel + *samplePtr) * mixVolume;
        }
    }

    // Return the product of the final gain and the mixer volume
    return (float)(mixVolume * gain);
}