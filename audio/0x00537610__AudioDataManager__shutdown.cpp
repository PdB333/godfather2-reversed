// FUNC_NAME: AudioDataManager::shutdown
void __fastcall AudioDataManager::shutdown()
{
    // Store the manager pointer in a global singleton reference (DAT_012058e8)
    gAudioManager = this;

    // Release two resources stored at offsets +0x10 and +0x14 (likely child objects or buffers)
    releaseResource(*(void**)(reinterpret_cast<char*>(this) + 0x10));
    releaseResource(*(void**)(reinterpret_cast<char*>(this) + 0x14));
}