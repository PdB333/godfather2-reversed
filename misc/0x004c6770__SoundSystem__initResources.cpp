// FUNC_NAME: SoundSystem::initResources
void __thiscall SoundSystem::initResources() {
    uint32_t soundBufferHandle = OpenAudioDevice(); // 0x0060a380
    *(uint32_t*)(this + 0x10) = soundBufferHandle; // +0x10: sound buffer handle
    uint32_t streamHandle = LoadSoundFile(gDefaultSoundFilePath); // 0x0060a2e0, PTR_DAT_0110a36c
    *(uint32_t*)(this + 0x14) = streamHandle; // +0x14: stream handle
    StartAudioMixer(); // 0x006127d0
}