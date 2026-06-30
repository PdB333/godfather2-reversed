// FUNC_NAME: AudioSystem::initialize
// Function address: 0x00618190
// Role: Initializes the audio system with optional sound bank and stream handles.
// Stores pointers at offsets 0x10 and 0x14.

void __thiscall AudioSystem::initialize(int soundBankHandle, int streamHandle)
{
    // If a sound bank handle is provided, acquire the sound bank pointer
    if (soundBankHandle != 0) {
        // Call to get/create sound bank (returns pointer)
        unsigned int uVar1 = FUN_0060a380(); // Likely SoundBank::getInstance()
        *(unsigned int *)(this + 0x10) = uVar1; // +0x10: m_pSoundBank
    }
    // If a stream handle is provided, acquire the stream resource pointer
    if (streamHandle != 0) {
        // Call to get/create stream object (returns pointer)
        unsigned int uVar1 = FUN_0060a2e0(streamHandle); // Likely StreamManager::createStream()
        *(unsigned int *)(this + 0x14) = uVar1; // +0x14: m_pStreamManager
    }
    // Initialize audio engine subsystems
    FUN_006127d0(); // AudioEngine::init()
    FUN_006181d0(); // AudioSystem::finishSetup()
    return;
}