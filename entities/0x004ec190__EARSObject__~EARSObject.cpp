// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x004EC190
// Role: Destructor for EARSObject; switches vtable to destruction-specific table, releases child object via a global memory manager, then restores vtable.

void __thiscall EARSObject::~EARSObject(EARSObject* this)
{
    // +0x00: vfptr (vtable pointer)
    // +0x20: m_childObject (pointer to owned child object)

    // Set vtable to destruction-specific vtable (PTR_FUN_00e372b4)
    this->vfptr = reinterpret_cast<void**>(&PTR_FUN_00e372b4);

    // If child object exists, release it through the global memory manager vtable at 0x01194538
    if (this->m_childObject != nullptr)
    {
        // g_memoryManagerVtable is a global pointer to an array of function pointers
        // Offset +0x04 (index 1) is the release/destroy function accepting (void*, int)
        typedef void (__stdcall *ReleaseFunc)(void*, int);
        ReleaseFunc releaseFunc = reinterpret_cast<ReleaseFunc>((*reinterpret_cast<void***>(DAT_01194538))[1]);
        releaseFunc(this->m_childObject, 0);
    }

    // Restore vtable to original class vtable (PTR_LAB_00e3729c) before returning
    this->vfptr = reinterpret_cast<void**>(&PTR_LAB_00e3729c);
}