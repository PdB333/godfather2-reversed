// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
    // Vtable table at 0x00e356ac (base class vtable)
    this->vfptr = (void**)&Vtable_00e356ac;

    // Unlink this from the intrusive doubly linked list.
    // Fields:
    // +0x48: m_pNext (pointer to next node)
    // +0x4C: m_pPrev (pointer to previous node)
    UnlinkNode(this, (void**)&this->m_pNext);

    // Switch vtable to second base (0x00e35680)
    this->vfptr = (void**)&Vtable_00e35680;

    // Conditionally call cleanup function (e.g., stop sounds, release resources)
    // +0x40: m_bFlag1 (0 if not set), +0x3C: m_bFlag2, +0x1C: m_pOwner
    // m_pOwner->m_bActive at +0x44
    if (((this->m_bFlag1 != 0) || (this->m_bFlag2 != 0)) &&
        (this->m_pOwner != null) && (*(char*)(this->m_pOwner + 0x44) == '\0'))
    {
        // Called to stop sound or perform cleanup
        CleanupSoundEffects(); // FUN_004abd20
    }

    // Final vtable for the most derived class
    this->vfptr = (void**)&Vtable_00e414e0;

    // Decrement reference count on the object pointed to by +0x08 (m_pRefCountObj)
    // The function returns a pointer to a short at +0x12 that is decremented
    short* refCount = (short*)DecrementReferenceCounter(this->m_pRefCountObj); // FUN_00621530
    *refCount = *refCount - 1;
}