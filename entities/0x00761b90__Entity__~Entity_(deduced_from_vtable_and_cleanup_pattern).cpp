// FUNC_NAME: Entity::~Entity (deduced from vtable and cleanup pattern)
void __fastcall Entity::~Entity(Entity* this)
{
    // Set vtable to base class (likely Entity base vtable) to ensure proper virtual calls during destruction
    this->vtable = &g_EntityVTable; // PTR_LAB_00d654e8

    // Deallocate or prepare a sub-object of size 0x44 (68 bytes) - likely a data block or embedded structure
    g_HeapAllocator::deallocate(0x44); // FUN_007f6420

    // Access sub-object at offset +0x50 (this->m_pSubObject)
    SubObject* subObj = this->m_pSubObject;

    // Copy pointer from this at +0x7c (this->m_ownerPointer) into sub-object at +0x5c4
    subObj->m_backPointer = this->m_ownerPointer;

    // Clear bit 1 (0x2) in sub-object's flags at +0x564
    subObj->m_flags &= ~0x2;

    // Release three reference-counted objects (pointers at +0x74, +0x60, +0x54)
    if (this->m_pResourceA != 0) // +0x74
    {
        g_RefCounted::release(this->m_pResourceA); // FUN_004daf90
    }
    if (this->m_pResourceB != 0) // +0x60
    {
        g_RefCounted::release(this->m_pResourceB);
    }
    if (this->m_pResourceC != 0) // +0x54
    {
        g_RefCounted::release(this->m_pResourceC);
    }

    // Final cleanup (likely free the entity memory or call base destructor chain)
    g_ObjectMemoryManager::finalizeShutdown(); // FUN_004ac1e0
}