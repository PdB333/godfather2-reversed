// FUNC_NAME: EARSStream::initialize

// Constructor/initializer for an EARS stream object.
// Sets up stream handle and binds to a global audio system.
// Result: returns pointer to this object (param_1 / this).
EARSStream* __thiscall EARSStream::initialize(EARSStream* this)
{
    int* pAudioSystem;
    int unusedParams[3] = {0, 0, 0}; // placeholder for some output or parameters
    int streamHandle;

    // Initialize handle to invalid (-1) and type to 0
    this->streamHandle = -1;          // +0x00
    this->streamType = 0;             // +0x04

    // Get pointer to the audio system singleton (+8 offset from global base)
    pAudioSystem = *(int**)(g_globalBase + 8); // g_globalBase at 0x01223414

    // Acquire stream handle via engine call (e.g., OpenStream)
    streamHandle = FUN_004265d0(unusedParams, pAudioSystem);
    this->audioHandle = streamHandle; // +0x14
    this->audioSystem = pAudioSystem; // +0x18

    // Call virtual method at vtable+8 (e.g., InitSystem)
    (**(code**)(*pAudioSystem + 8))();

    // Reset other fields
    this->field_0x08 = 0; // +0x08
    this->field_0x0C = 0; // +0x0C
    this->field_0x10 = 0; // +0x10

    return this;
}