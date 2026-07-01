// FUNC_NAME: AudioManager::playAudioEvent
void __fastcall AudioManager::playAudioEvent(int this)
{
    // +0x90: pointer to active sound data or stream
    if (*(int *)(this + 0x90) != 0) {
        // +0x10c: sound ID or bank handle
        // 0x1a: sound channel/priority (e.g., kChannelVoice = 26)
        // Last three zeros: flags (loop, spatial, etc.)
        int soundHandle = FUN_0090e2d0(*(int *)(this + 0x10c), *(int *)(this + 0x90), 0x1a, 0, 0, 0);
        *(int *)(this + 0x110) = soundHandle; // +0x110: store playback handle
        FUN_009847c0(0xffffffff); // debug release or log call with -1 as sentinel
    }
}