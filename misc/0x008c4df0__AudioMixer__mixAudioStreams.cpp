// FUNC_NAME: AudioMixer::mixAudioStreams
void __fastcall AudioMixer::mixAudioStreams()
{
    uint totalStreamCount = this->mSourceStreamCount + this->mEffectStreamCount;
    if (totalStreamCount == 0) {
        return;
    }

    VolumeControl* volumeCtrl = this->mVolumeControl;  // +0x1d0
    float desiredScale = 0.0f;
    if (volumeCtrl != nullptr) {
        desiredScale = volumeCtrl->mVolume * this->mMasterVolume;  // +0x58, +0x188
    }

    float baseVal = (float)this->mBaseSampleCount;  // +0x13c
    if (this->mBaseSampleCount < 0) {
        baseVal += 8388608.0f;  // DAT_00e44578 (likely NaN handling)
    }
    float totalDesiredBase = baseVal * desiredScale + this->mSampleOffset;  // +0x104

    float scaleFactor;
    if (volumeCtrl != nullptr) {
        scaleFactor = volumeCtrl->mVolume * this->mMasterVolume;
    } else {
        scaleFactor = 0.0f;
    }

    int totalDesired;
    if ((totalDesiredBase / scaleFactor) <= 0.0f) {
        totalDesired = 0;
    } else {
        totalDesired = (int)(totalDesiredBase / scaleFactor);
    }

    if (totalDesired <= 0) {
        return;
    }

    // Allocate temporary mix buffer (12 bytes per stream)
    StreamMixEntry* mixBuffer = (StreamMixEntry*)allocArray(totalStreamCount * sizeof(StreamMixEntry));  // FUN_009c8e80
    float totalContrib = 0.0f;
    uint streamIndex = 0;

    // Process source streams
    for (uint i = 0; i < this->mSourceStreamCount; i++) {
        AudioStream* stream = this->mSourceStreams[i];  // +0x108
        float contrib = getStreamContribution(stream, &mixBuffer[streamIndex]);  // FUN_008c4d30
        totalContrib += contrib;
        streamIndex++;
    }

    // Process effect streams
    for (uint i = 0; i < this->mEffectStreamCount; i++) {
        AudioStream* stream = this->mEffectStreams[i];  // +0x114
        float contrib = getStreamContribution(stream, &mixBuffer[streamIndex]);
        totalContrib += contrib;
        streamIndex++;
    }

    float scale = (float)totalDesired / totalContrib;
    bool anyLimited = false;
    uint entryIndex = 0;

    // First pass: assign sample counts, limit by per-stream maximum
    for (uint i = 0; i < totalStreamCount; i++) {
        AudioStream* stream = mixBuffer[entryIndex].stream;
        if (stream == nullptr) continue;  // safety

        uint desiredSamples = floorFloatToUint(scale * mixBuffer[entryIndex].contribution);  // FUN_008bd720
        uint streamMax = stream->mMaxSamples;  // +0x64 (100)

        if (streamMax < desiredSamples) {
            totalDesired -= streamMax;
            totalContrib -= mixBuffer[entryIndex].contribution;
            mixBuffer[entryIndex].finalSamples = streamMax;
            anyLimited = true;

            // If stream is not hardware (flag == 0), adjust buffer
            if (stream->mFlags == 0) {  // +0xfc
                uint currentBufSize = getCurrentBufferSize();  // FUN_006b18a0
                if (currentBufSize < streamMax) {
                    addSamplesToBuffer(stream->mBufferHandle, streamMax - currentBufSize, 1);  // FUN_008c0b10
                } else if (streamMax < currentBufSize) {
                    removeSamplesFromBuffer(stream->mBufferHandle, currentBufSize - streamMax);  // FUN_008be590
                }
            }

            // Call some update function (with entryIndex offsetting) – FUN_008bdf90
            audioStreamUpdated(entryIndex);
            entryIndex--;  // because the loop increments later? Actually the code decrements local_18 and iVar7 by -0xc
        } else {
            mixBuffer[entryIndex].finalSamples = desiredSamples;
        }
        entryIndex++;
    }

    // Second pass: redistribute remaining if any stream was limited
    if (anyLimited && totalDesired > 0) {
        float newScale = (float)totalDesired / totalContrib;
        for (uint i = 0; i < totalStreamCount; i++) {
            AudioStream* stream = mixBuffer[i].stream;
            uint desiredSamples = floorFloatToUint(newScale * mixBuffer[i].contribution);
            if (stream->mMaxSamples < desiredSamples) {
                mixBuffer[i].finalSamples = stream->mMaxSamples;
            } else {
                mixBuffer[i].finalSamples = desiredSamples;
            }

            // Update buffers
            if (stream->mFlags == 0) {
                uint currentBufSize = getCurrentBufferSize();  // FUN_006b18a0
                uint handle = stream->mBufferHandle;  // +0x38
                if (currentBufSize < mixBuffer[i].finalSamples) {
                    addSamplesToBuffer(handle, mixBuffer[i].finalSamples - currentBufSize, 1);
                } else if (mixBuffer[i].finalSamples < currentBufSize) {
                    uint diff = currentBufSize - mixBuffer[i].finalSamples;
                    if (diff <= this->mRemainingCapacity) {  // +0x140
                        this->mRemainingCapacity -= diff;
                        if (isSoundActive(handle) && diff <= getCurrentBufferSize()) {  // FUN_006b0ee0, FUN_006b18a0
                            consumeFromBuffer(diff);  // FUN_006b64b0
                        }
                    }
                }
            }
        }
    }

    // Free temporary buffer
    deallocArray(mixBuffer);  // FUN_009c8f10
}