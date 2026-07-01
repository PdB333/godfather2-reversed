//FUNC_NAME: AudioManager::initializeAudioChannels

void __fastcall AudioManager::initializeAudioChannels(int *this)
{
    int i;
    float volume;

    // One-time initialization of audio system (8 calls to some setup function)
    if ((g_audioInitFlag & 1) == 0) {
        g_audioInitFlag |= 1;
        for (i = 0; i < 8; i++) {
            FUN_008970c0(); // likely audio subsystem init step
        }
    }

    // Enable 9 audio channels (bitmask 1,2,4,8,0x10,0x20,0x40,0x80,0x100)
    FUN_008970e0(1, g_audioChannelConfig, 1);
    FUN_008970e0(2, g_audioChannelConfig, 1);
    FUN_008970e0(4, g_audioChannelConfig, 1);
    FUN_008970e0(8, g_audioChannelConfig, 1);
    FUN_008970e0(0x10, g_audioChannelConfig, 1);
    FUN_008970e0(0x20, g_audioChannelConfig, 1);
    FUN_008970e0(0x40, g_audioChannelConfig, 1);
    FUN_008970e0(0x80, g_audioChannelConfig, 1);
    FUN_008970e0(0x100, g_audioChannelConfig, 1);

    // Initialize audio buffer with 9 channels and 4 bytes per sample?
    FUN_00897410(&g_audioBuffer, 9, 4);

    // Get current volume from virtual function (vtable+0xC4) and apply to audio output object
    // this[0x17d] is offset 0x5F4, likely a pointer to an audio output device
    int *audioOutput = (int *)this[0x17d]; // +0x5F4
    volume = (**(float (__thiscall **)(int *))(*this + 0xC4))(); // virtual function returning float
    (**(void (__thiscall **)(int *, float))(audioOutput[0] + 0x3C))(audioOutput, volume); // set volume on output
}