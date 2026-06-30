// FUNC_NAME: AudioDataManager::initialize
void __thiscall AudioDataManager::initialize()
{
    // Get handle from audio output manager (likely returns a mixer or stream ID)
    uint field_10 = FUN_0060a380();
    this->field_0x10 = field_10;

    // Initialize secondary audio resource using global data pointer (PTR_DAT_00f1747c -> master audio config)
    uint field_14 = FUN_0060a2e0(&PTR_DAT_00f1747c);
    this->field_0x14 = field_14;

    // Finalize audio setup (e.g., start playback, set default state)
    FUN_006127d0();
}