// FUNC_NAME: AudioDataManager::~AudioDataManager
void __fastcall AudioDataManager::~AudioDataManager(AudioDataManager* this)
{
    // Set vtable to derived class vtable (0x00e3a038)
    this->vtable = reinterpret_cast<VTable*>(0x00e3a038);
    // Set secondary vtable pointer (offset +0x04) to base class vtable (0x00e3a054)
    this->m_baseVtable = reinterpret_cast<VTable*>(0x00e3a054);

    // Check if resource pointer at offset 0x34 (index 0xd) is non-null
    if (this->m_resourcePtr != nullptr) {
        // Release the resource (calls cleanup function 0x009f1b20)
        AudioDataManager::releaseResource(this);
        // Perform global cleanup (function 0x009f01a0)
        audioCleanupGlobal();
    }

    // Switch to base class vtable (0x00dc3dd4) for final destruction
    this->m_baseVtable = reinterpret_cast<VTable*>(0x00dc3dd4);
    // Set primary vtable to purecall handler (0x00e3924c) to invalidate object
    this->vtable = reinterpret_cast<VTable*>(0x00e3924c);
}