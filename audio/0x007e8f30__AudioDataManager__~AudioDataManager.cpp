// FUNC_NAME: AudioDataManager::~AudioDataManager
// Function address: 0x007e8f30
// Destructor of AudioDataManager (EA EARS engine)
// Releases held soundbank resource, shuts down global singleton, and cleans up.

void __fastcall AudioDataManager::destructor(AudioDataManager* this)
{
    int resourceHandle;
    int iVar2;

    // Set vtable pointer to this class's vtable
    this->vtable = &AudioDataManager_vtable_initial; // +0x00
    this->someOtherVtable = &AudioDataManager_vtable_secondary; // +0x04
    this->someVtable3 = &AudioDataManager_vtable_tertiary; // +0x10

    resourceHandle = 0;

    // Attempt to get a soundbank resource by its hash ID (0xded51537)
    iVar2 = ResourceManager::getResource(0xded51537, &resourceHandle);

    // If resource exists and this object's flag at +0x14 is set, release it
    if ((iVar2 != 0) && (this->soundbankFlag != '\0')) {
        this->soundbankFlag = '\0';
        ResourceManager::releaseResource(0xded51537);
    }

    // If the global singleton pointer is valid, perform shutdown sequence
    if (g_pAudioDataManager != nullptr) {
        AudioDataManager::shutdown(1);       // Shutdown with flag 1
        someGlobalReleaseFunc(*g_pAudioDataManager);  // Release first dword (vtable?)
        someGlobalCleanupFunc(g_pAudioDataManager);   // Cleanup pointer
    }

    // Clear global singleton pointer
    g_pAudioDataManager = nullptr;
    this->someVtable3 = &AudioDataManager_vtable_final; // +0x10
    g_bAudioInitialized = 0;

    // Final global cleanup
    GlobalShutdownFunction();

    // Set vtable to base class vtable
    this->vtable = &BaseClass_vtable; // +0x00
}