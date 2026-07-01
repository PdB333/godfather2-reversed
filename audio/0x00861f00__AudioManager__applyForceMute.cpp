// FUNC_NAME: AudioManager::applyForceMute
void __thiscall AudioManager::applyForceMute(AudioManager* this) {
    // Check if bit 0x8000 is not already set on the force mute flag (at offset +0xC88)
    int forceMuteFlag = this->forceMuteFlag; // +0x322*4 = +0xC88
    if ((forceMuteFlag | 0x8000U) != forceMuteFlag) {
        // Call virtual function at vtable+0x28 on the stream manager object (at +0x16*4 = +0x58)
        // Parameter 0x10 likely indicates a buffer size or type
        this->streamManager->allocate(0x10); // vtable offset 0x28
        // Set the bit to mark force mute active
        this->forceMuteFlag |= 0x8000;
    }

    // Check global pointer to a subobject (DAT_012233a0+4 points to a member of a larger object)
    AudioManager* globalAudioMgr = *(int**)(DAT_012233a0 + 4);
    if (globalAudioMgr != nullptr) {
        // Recover base of the containing object (member at +0x1f30)
        AudioManager* baseObj = reinterpret_cast<AudioManager*>(reinterpret_cast<char*>(globalAudioMgr) - 0x1f30);
        // Call virtual function at vtable+0x2c4 on this object (likely apply state to global manager)
        this->applyState(baseObj); // vtable offset 0x2c4
    } else {
        // No global manager, call with null
        this->applyState(nullptr);
    }
}