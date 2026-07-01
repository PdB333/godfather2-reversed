// FUNC_NAME: AudioDataManager::shutdown
void __fastcall AudioDataManager::shutdown(undefined4 *this)
{
    // Set vtable to derived class vtable
    this[0] = &PTR_LAB_00d6ed08;  // derived vtable

    // Clear bit 0 of flags at offset 0xAC (this[0x2b])
    this[0x2b] = this[0x2b] & 0xfffffffe;

    // Null out pointer at offset 0x7C (this[0x1f])
    this[0x1f] = 0;

    // Release various audio resources (global functions)
    releaseAudioEngine(0);
    releaseStreamEngine(0);
    freeAudioBank(0);
    freeAudioBuffer(0);
    stopAllStreams(0);

    // Release specific stream slots (indices: 95, 63, 62, 61, 73)
    releaseStreamByIndex(0x5f);
    releaseStreamByIndex(0x3f);
    releaseStreamByIndex(0x3e);
    releaseStreamByIndex(0x3d);
    releaseStreamByIndex(0x49);

    // Switch to base class vtable and call base destructor
    this[0] = &PTR_LAB_00d6b95c;   // base vtable
    baseShutdown();                // FUN_0080ea60

    return;
}