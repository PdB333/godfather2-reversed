// FUN_NAME: AudioComponent::initialize
void __fastcall AudioComponent::initialize(AudioComponent* this)
{
    // Initialize global audio system (likely loads sound banks)
    initGlobalAudio();

    // Copy sound data references from global arrays into this component's members
    // +0x54: m_pSoundHandle1
    assignSoundHandle(&g_SoundData1, &this->m_pSoundHandle1, 0, 0, 0, 1);
    // +0x58: m_pSoundHandle2
    assignSoundHandle(&g_SoundData2, &this->m_pSoundHandle2, 0, 0, 0, 1);
    // +0x5c: m_pSoundHandle3
    assignSoundHandle(&g_SoundData3, &this->m_pSoundHandle3, 0, 0, 0, 1);
    // +0x60: m_pSoundHandle4
    assignSoundHandle(&g_SoundData4, &this->m_pSoundHandle4, 0, 0, 0, 1);
}