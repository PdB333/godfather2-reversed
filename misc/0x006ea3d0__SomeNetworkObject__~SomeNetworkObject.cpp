// FUNC_NAME: SomeNetworkObject::~SomeNetworkObject
SomeNetworkObject* __thiscall SomeNetworkObject::~SomeNetworkObject(SomeNetworkObject* this, byte allocFlag)
{
    // Set vtable pointers to ensure correct virtual dispatch during destruction
    this->vtable = &SomeNetworkObject_vtable;          // primary vtable
    this->secondaryVtable1 = &SomeNetworkObject_vtable2; // +0x3C
    this->secondaryVtable2 = &SomeNetworkObject_vtable3; // +0x48

    // Decrement global instance count (singleton reference)
    decrementGlobalCounter(&g_NetworkObjectCount); // DAT_0120e93c

    // Destroy contained subobject at offset 0x70 (e.g., an array or event handler)
    destroySubObject(this + 0x1C); // offset 0x70

    // If there is an attached custom destructor, invoke it
    if (this->m_pCustomDestructorData != nullptr) { // +0x60
        (this->m_pCustomDestructorFunc)(this->m_pCustomDestructorData); // +0x6C
    }

    // Perform global cleanup (e.g., release shared resources)
    globalCleanup();

    // Free memory if this object was dynamically allocated
    if ((allocFlag & 1) != 0) {
        operator delete(this, 0x8C);
    }

    return this;
}