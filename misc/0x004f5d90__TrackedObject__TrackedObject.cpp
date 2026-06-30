// FUNC_NAME: TrackedObject::TrackedObject
void __fastcall TrackedObject::TrackedObject(TrackedObject* this)
{
    // Set vtable to base class (before calling base constructors)
    this->vtable = &BASE_VTABLE_00e37828;
    BaseClassConstructor(); // FUN_004ebba0 - likely base class constructor
    DerivedClassAdditionalInit(); // FUN_004f70f0 - initializes additional members
    // Overwrite vtable to derived class after base construction
    this->vtable = &DERIVED_VTABLE_00e37110;

    // Check if the object has a valid pointer stored at offset +0x10
    int* pData = this->m_pSomeData; // offset +0x10
    if (pData != nullptr)
    {
        // Access the global pool manager's free list head: stored at address (0x01206880 + 0x14)
        // This is a pointer to a free node in the pool.
        int** ppFreeHead = (int**)((unsigned char*)&g_poolManager + 0x14);
        // First word of the current free node: it is a pointer to next free node.
        // We overwrite it with a sentinel vtable (label address) for the node type.
        **(int***)ppFreeHead = (int*)&NODE_VTABLE_01123be8;
        // Advance the free list head by 4 bytes (past the vtable slot)
        *ppFreeHead = (int*)((unsigned char*)*ppFreeHead + 4);
        // Write the object's stored pointer into the second slot of the node
        **(int**)ppFreeHead = (int)pData;
        // Advance again (past the data slot)
        *ppFreeHead = (int*)((unsigned char*)*ppFreeHead + 4);
        // Clear the object's fields that were used to pass the pointer
        this->m_pSomeData = nullptr;      // offset +0x10
        this->m_pSomeDataBackup = nullptr; // offset +0x14
    }
}