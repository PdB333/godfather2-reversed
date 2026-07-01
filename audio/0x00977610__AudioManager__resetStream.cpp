// FUNC_NAME: AudioManager::resetStream
// Address: 0x00977610
// Clears the active audio stream and resets the manager flag.

extern class AudioManager* g_pAudioManager; // DAT_0112af70
extern int32_t g_streamHandle;              // DAT_01130408

extern void sub_408A00(int32_t* handle, int32_t flags);

int AudioManager::resetStream() {
    // Clear active stream flag at offset +0x14C
    g_pAudioManager->m_activeStream = 0;

    int32_t handle = g_streamHandle;
    sub_408A00(&handle, 0);

    return 1;
}