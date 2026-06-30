// FUNC_NAME: Entity::constructor

Entity* __thiscall Entity::constructor(Entity* this, bool fromHeap)
{
    // Set vtable pointer
    this->vftable = &g_EntityVtable; // PTR_FUN_00d5ef34

    // Initialize secondary pointer at offset +0x08
    this->m_pSomeData = &g_SomeData; // PTR_LAB_00d5ef2c

    // Check if sub-object at offset +0xE8 (index 58) is allocated; clean it up if so
    if (this->m_pSubObject != nullptr)
    {
        // Likely a destructor or release function
        FUN_004daf90(&this->m_pSubObject);
    }

    // Perform common initialization (e.g., base class init)
    FUN_006c9820();

    // If the object was allocated from the heap, register it with the object manager
    if (fromHeap)
    {
        ObjectManager* manager = (ObjectManager*)FUN_009c8f80();
        // registerObject typically stores the object pointer and its size for tracking
        manager->registerObject(this, sizeof(Entity)); // 0x310 = 784 bytes
    }

    return this;
}