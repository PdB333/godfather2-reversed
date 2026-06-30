// FUNC_NAME: SomeManager::shutdown

void __thiscall SomeManager::shutdown(SomeManager *this)
{
    // Buffer for temporary data (12 bytes)
    unsigned char tempBuffer[12];

    // Copy data from objectB into tempBuffer (likely storing state before destruction)
    // FUN_005e0410 signature: void copyAndStore(void* dest, SomeManager* mgr, ObjectB* obj, SomeManager* mgr2, ObjectB* obj2)
    copyAndStore(tempBuffer, this, *(ObjectB**)(this + 0x1C), this, *(ObjectB**)(this + 0x1C));

    // Release objectB with size parameter 0x18
    // ObjectB's vtable[1] (offset +4) is a release method taking a size parameter
    (*(void (**)(ObjectB*, int))(*(int*)(*(int*)(this + 0x1C)) + 4))(*(ObjectB**)(this + 0x1C), 0x18);

    // Clear objectB pointer and associated field
    this->m_pObjectB = 0;   // +0x1C
    this->m_objectBSize = 0; // +0x20

    // If m_objectAData exists, release it via objectA
    if (this->m_objectAData != 0) { // +0x18
        // ObjectA's vtable[1] is a release method taking two args: data and a flag
        (*(void (**)(ObjectA*, int, int))(*(int*)(*(int*)(this + 0x14)) + 4))(*(ObjectA**)(this + 0x14), this->m_objectAData, 0);
        this->m_objectAData = 0; // +0x18
    }

    // Shutdown objectA completely via its vtable[3] (offset +0xC) with no args
    (*(void (**)(ObjectA*))(*(int*)(*(int*)(this + 0x14)) + 0xC))(*(ObjectA**)(this + 0x14));

    // Global cleanup routine for the manager
    globalCleanup(); // FUN_005df430
}