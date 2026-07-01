// FUNC_NAME: MultiTrackStream::processInterpolation
float __thiscall MultiTrackStream::processInterpolation(void* this, float inputA, float inputB, float inputC, float rate, float unknown, float* pData, float* pState) {
    float* origData = pData;          // Store original pointer (struct)
    float* dataPtr = (float*)(int)*pData; // First element of pData is a pointer to sample data (cast to int to avoid direct pointer arithmetic warning)

    // Check some threshold from this object at offset 0x7AC
    if (g_frequencyCutoff < *(float*)((char*)this + 0x7AC)) {
        // Multiply the data pointer by a scale factor from offset 0x7B0 (likely phase increment)
        dataPtr = (float*)(*(float*)((char*)this + 0x7B0) * (int)dataPtr);
    }

    // Call underlying interpolation function (likely cubic or linear)
    float10 result = FUN_007f6550(inputA, inputB, inputC, pState[0], rate, pState[1], dataPtr, origData[2], unknown);

    float outputSample = (float)result;

    // Conditional gain adjustment based on bitmask and constants
    float maskedPhase = (float)((int)pState[1] & g_phaseMask);
    if (maskedPhase <= g_phaseOffset) {
        outputSample = (maskedPhase * g_phaseMultiplier + g_phaseOffset) * outputSample;
    }

    float previousOutput = pState[0];
    // Update phase if rate exceeds cutoff
    if (g_frequencyCutoff < rate) {
        pState[1] = outputSample / rate;
    }
    // Accumulate sample
    pState[0] = previousOutput + outputSample;

    return previousOutput + outputSample;
}