// FUNC_NAME: AudioManager::releaseResources
// Function at 0x00924170: Releases two audio resources and optionally performs cleanup based on a flag.
// Class AudioManager (hypothetical) - likely part of EARS audio system.
// Offsets:
//   +0x70: m_pStreamHandle1 (uint32, pointer to stream object)
//   +0x74: m_pStreamHandle2 (uint32, pointer to stream object)
//   +0x78: m_bIsPrimary (int, flag indicating primary stream)

void __thiscall AudioManager::releaseResources(void)
{
    // Release first audio stream handle
    releaseStreamHandle(*(uint32 *)(this + 0x70));
    // Release second audio stream handle
    releaseStreamHandle(*(uint32 *)(this + 0x74));
    // Conditional cleanup: if m_bIsPrimary == 1, perform additional cleanup
    performCleanup(*(int *)(this + 0x78) == 1);
    // Global audio system shutdown call
    shutdownAudioSystem();
}