// FUNC_NAME: AudioPlayer::interpolateSample
// Function address: 0x005909a0
// Performs interpolation on a sample from an audio stream; returns extended-precision float.

float10 AudioPlayer::interpolateSample(StreamState* streamState, SampleState* sampleState)
{
    float sampleValue;
    uint sampleCount;
    int* currentIndexPtr;
    float currentSample;
    float interpolatedSample;

    currentIndexPtr = sampleState;  // sampleState points to struct: +0 = float* sampleArray, +4 = int currentIndex

    // Initialize or validate parameters (likely checks pointers)
    FUN_005913b0(this, streamState, sampleState);

    // Read total sample count from stream state: streamState->somePointer->count at +0x0C
    sampleCount = *(uint*)(*(int*)(streamState + 4) + 0x0C);

    // Check if current index is out of bounds (<= count indicates error)
    if (currentIndexPtr[1] <= sampleCount) {
        sampleState = (int*)0x0;
        FUN_00591c00(&sampleState);  // Reset or handle error
    }

    // Fetch the target sample value from the sample array at index sampleCount (not currentIndex – possibly intended sampleCount)
    sampleValue = *(float*)(*currentIndexPtr + sampleCount * 4);

    // If stream state is in a specific mode (byte at +1 < 2), return constant (likely 1.0f)
    if (*(char*)(streamState + 1) < 2) {
        return (float10)DAT_00e2b1a4;  // Constant (probably 1.0f)
    }

    currentSample = sampleValue;  // Save fetched sample

    // Perform two calls to a function (possibly conversion or timing)
    FUN_00591160();
    sampleState = (int*)currentSample;  // Reinterpret sample as pointer (hack for output)
    FUN_00591160();

    // Interpolation logic
    if (sampleValue <= 0.0f) {
        return (float10)(float)sampleState;  // Return current sample (if sampleValue <= 0)
    }

    interpolatedSample = currentSample;
    if ((sampleValue < DAT_00e2b1a4) && (interpolatedSample = (float)sampleState, (float)sampleState != currentSample)) {
        // Linear interpolation: currentSample - previousSample * sampleValue + previousSample
        return (float10)((currentSample - (float)sampleState) * sampleValue + (float)sampleState);
    }

    return (float10)interpolatedSample;
}