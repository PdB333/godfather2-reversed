// FUNC_NAME: AudioEngine::validateBufferSize
// Address: 0x0061aad0
void AudioEngine::validateBufferSize(uint bufferSize, void* streamPointer)
{
    // Check: stream must be valid and buffer size must be a power of two
    if ((streamPointer != nullptr) && ((bufferSize & (bufferSize - 1)) != 0))
    {
        double dBufferSize = (double)(int)bufferSize;
        FUN_00d3d41f();                 // Unknown math operation (maybe fsqrt or ftoi)
        FUN_00d3d41f();                 // Called twice (double? st(0) manipulated)
        double globalScale = DAT_00e44650; // Global scale constant (e.g., sample rate divisor)
        FUN_00b9af10();                 // Unknown state setup
        FUN_00b9cce0((double)((float)dBufferSize / (float)globalScale)); // Divide and convert
        FUN_00b9a7b0();                 // Finalize or apply result
    }
}