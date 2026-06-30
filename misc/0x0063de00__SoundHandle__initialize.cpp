// FUNC_NAME: SoundHandle::initialize

void SoundHandle::initialize(void* ownerObj) // this in ESI, ownerObj in EAX
{
    // Get the game's stream manager (singleton)
    void* streamMgr = StreamManager::getInstance(); // FUN_0063dd40

    // Allocate a 4‑byte handle from the owner's memory pool
    int allocSize = 4;
    void* handleData = MemoryAllocator::allocate(
        *(void**)((char*)ownerObj + 0x1c),  // offset 0x1c: memory pool pointer
        &allocSize);                        // FUN_00642970

    // Initialize the handle structure fields
    this->type       = 4;                    // +0x00: type identifier (e.g., kWaveStream)
    this->dataPtr    = handleData;           // +0x04: allocated data pointer
    this->field_0x08 = 0;                    // +0x08: not set, left uninitialized (safe default)
    this->field_0x0C = -1;                   // +0x0C: sentinel / invalid ID
    this->field_0x10 = -1;                   // +0x10: sentinel / invalid ID
}