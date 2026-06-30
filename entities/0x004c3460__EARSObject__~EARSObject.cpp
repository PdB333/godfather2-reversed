// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(EARSObject *this)
{
    // +0x00: Set vtable pointer to the base class vtable
    *(void***)this = (void**)&PTR_FUN_00e36290;

    // Call the internal destructor body (destroys member objects, calls base destructor)
    this->destroySubobjects(); // FUN_004c33a0

    // +0x208: If a resource pointer exists, release it (e.g., a file handle or asset node)
    if (this->m_pResource != nullptr)
    {
        ::releaseResource(this->m_pResource); // FUN_009c8f10
    }

    // Perform final cleanup (e.g., free memory, remove from managers)
    this->finalize(); // FUN_004c27f0
}