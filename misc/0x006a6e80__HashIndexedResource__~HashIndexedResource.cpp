// FUNC_NAME: HashIndexedResource::~HashIndexedResource
void __fastcall HashIndexedResource::~HashIndexedResource(HashIndexedResource* this) {
    // Set vtables for destruction order (base classes)
    this->vtable = &destructorVtable_0xd5d7e0;        // +0x00
    this->baseVtable1 = &baseClass1DestructorVtable;  // +0x3C
    this->baseVtable2 = &baseClass2DestructorVtable;  // +0x48

    // Decrement external reference counter (or unregister)
    decrementRefCount(&globalRefCounter_0x120e93c);   // FUN_004086d0

    // If secondary resource flag is set, clean that up too
    if (this->m_hasSecondaryResource) {               // byte at +0x70
        decrementRefCount(&secondaryGlobalRefCounter); // DAT_012069c4
    }

    // If any part of the hash key is nonzero, remove from hash table
    if (this->m_hashKey1 != 0 || this->m_hashKey2 != 0 ||
        this->m_hashKey3 != 0 || this->m_hashKey4 != 0) {
        uint32_t fullHash = ((this->m_hashKey1 * 0x21 + this->m_hashKey2) * 0x21 +
                            this->m_hashKey3) * 0x21 + this->m_hashKey4;
        removeFromHashTable(fullHash);                // FUN_006a54d0
    }

    // Free internal buffers
    releaseBuffer(this->m_buffer1);                   // FUN_00408310, +0x50
    releaseBuffer(this->m_buffer2);                   // FUN_00408310, +0x58

    // Final cleanup (probably global resource manager)
    cleanupResourceManager();                         // FUN_0046c640
}