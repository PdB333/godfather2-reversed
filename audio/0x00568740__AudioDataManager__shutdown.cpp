// FUNC_NAME: AudioDataManager::shutdown
void __thiscall AudioDataManager::shutdown(AudioDataManager *this)
{
    // Global flags: likely indicates whether the audio data manager is active/initialized
    g_audioDataManagerActive = 0; // DAT_0119a5b4
    g_audioDataManagerReady = 0;  // DAT_01198e7c

    // Clear internal state flag (offset +0x08)
    this->field_0x8 = 0;

    // Deallocate memory for the data pointer at offset +0x04
    // Parameters: pointer to free, and three zero flags (maybe size/type)
    deallocateMemory(this->field_0x4, 0, 0, 0); // FUN_00c796e0

    // Call virtual cleanup method at vtable offset 0x0C (likely destructor hook)
    this->vtable->cleanup(); // (**(code **)(*this + 0xc))()

    // Release additional resource for the same pointer
    releaseResource(this->field_0x4); // FUN_00c7a7c0

    // Nullify the pointer fields
    this->field_0x4 = 0;  // offset +0x04
    this->field_0xC = 0;  // offset +0x0C
}