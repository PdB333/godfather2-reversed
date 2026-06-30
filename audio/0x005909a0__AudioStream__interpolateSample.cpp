// FUNC_NAME: AudioStream::interpolateSample
float AudioStream::interpolateSample(void* this, AudioState* state, float** sampleBufferPtr) {
    float sampleValue;
    uint32_t sampleIndex;
    float* sampleArray;
    float interpolatedValue;
    float factor;

    sampleArray = *sampleBufferPtr; // save the actual array pointer

    FUN_005913b0(this, state, sampleBufferPtr); // presumably prepares state

    sampleIndex = *(uint32_t*)(*(int*)(state + 4) + 0xC); // state->someStruct->index

    if ((uint32_t)sampleArray[1] <= sampleIndex) {
        sampleBufferPtr = nullptr;
        FUN_00591c00(&sampleBufferPtr); // reset or advance buffer
    }

    sampleValue = *(float*)(*sampleBufferPtr + sampleIndex * 4); // read sample at index

    if (*(char*)(state + 1) < 2) { // state->playbackMode < 2
        return DAT_00e2b1a4; // default pitch value
    }

    interpolatedValue = sampleValue;
    FUN_00591160(); // some operation (e.g., get current time or update state)
    sampleBufferPtr = (float**)interpolatedValue; // reinterpret sample as pointer (likely union/void)
    FUN_00591160();

    if (sampleValue <= 0.0f) {
        return (float)sampleBufferPtr; // return reinterpreted value
    }

    factor = interpolatedValue;
    if ((sampleValue < DAT_00e2b1a4) && (factor = (float)sampleBufferPtr, (float)sampleBufferPtr != interpolatedValue)) {
        // Linear interpolation between two values
        return (interpolatedValue - (float)sampleBufferPtr) * sampleValue + (float)sampleBufferPtr;
    }
    return factor;
}