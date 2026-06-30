// FUNC_NAME: ChatterPlaybackManager::stopAllChatters
void ChatterPlaybackManager::stopAllChatters() {
    if (this->m_bPlaying != 0) {  // +0x1c: byte flag indicating active playback
        struct {
            int field_0;     // +0x00
            int field_4;     // +0x04
            char field_8;    // +0x08
        } local;

        local.field_0 = g_audioId;           // DAT_01221f34
        local.field_4 = 0;
        local.field_8 = 0;

        prepareAudio(&local, 0);              // FUN_00408a00: possibly set up audio string
        stopAudioChannel(&g_audioSource1, &g_audioSource2); // FUN_0059e490: stop specific audio
        this->m_bPlaying = 0;                 // clear flag
        destroyString(this + 0x14);           // FUN_004086d0: destruct sub-object at +0x14 (e.g., string)
        stopAllAudio(0);                      // FUN_0059e850: stop all audio
    }
}