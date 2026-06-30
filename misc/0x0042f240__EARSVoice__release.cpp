// FUNC_NAME: EARSVoice::release

void __thiscall EARSVoice::release(int reason)
{
    // If the voice handle is valid, release the audio resource
    if (this->m_voiceHandle != 0)
    {
        FUN_0049e4c0(this->m_voiceHandle, this->m_handleParam, reason);
        // Call a global callback for voice release notification
        ((void (*)())PTR_FUN_0110ac18)();
    }

    // Clear voice state and parameters
    this->m_state = 0;                // +0x60
    this->m_voiceHandle = 0;          // +0x64 (100)
    this->m_field68 = 0;              // +0x68
    this->m_field6c = 0;              // +0x6c
    this->m_field70 = 0;              // +0x70
    this->m_field74 = 0;              // +0x74
    this->m_handleParam = -1;         // +0x78

    // Ensure audio system is muted or disabled for this channel
    if (DAT_011da800 != 1)
    {
        // Call virtual function 0x198 on global audio manager: probably setMute(true)
        (**(code **)(*DAT_01205750 + 0x198))(DAT_01205750, 1, 1);
        DAT_011da800 = 1;
    }

    if (DAT_011da804 != 0)
    {
        // Call virtual function 400 (0x190) on global audio manager: probably setPause/reset
        (**(code **)(*DAT_01205750 + 0x190))(DAT_01205750, 1, 0, 0, 0);
        DAT_011da804 = 0;
    }
}