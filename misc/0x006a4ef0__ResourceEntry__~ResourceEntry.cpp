// FUNC_NAME: ResourceEntry::~ResourceEntry
void __fastcall ResourceEntry::~ResourceEntry(ResourceEntry* this)
{
    // Set vtable pointers for multiple base classes (offset 0x00, 0x3C, 0x48)
    this->vtable = &VTable1;                          // +0x00
    this->base2Vtable = &VTable2;                     // +0x3C
    this->base3Vtable = &VTable3;                     // +0x48

    // Release a static resource (probably audio asset container)
    staticRelease(&g_audioResourceA);                 // DAT_0120e93c -> some global

    // If the object owns a secondary audio resource, release it too
    if (this->m_bOwnsAudioResource) {                 // +0x18 (char/byte)
        staticRelease(&g_audioResourceB);             // DAT_012069c4
    }

    // Check if any of the four hash key parts are non-zero
    if (this->m_hashKeyPart1 != 0 || this->m_hashKeyPart2 != 0 ||
        this->m_hashKeyPart3 != 0 || this->m_hashKeyPart4 != 0) {
        // Compute a 128-bit key using the TNL hash multiplier (0x21 = 33)
        uint32 key = ((this->m_hashKeyPart0 * 0x21 + this->m_hashKeyPart1) * 0x21 +
                      this->m_hashKeyPart2) * 0x21 + this->m_hashKeyPart3;
        // Remove the entry from the hash table by key
        removeFromHashTable(key);
    }

    // Perform any final global cleanup
    globalCleanupCallback();
}