// FUNC_NAME: EARSObject::shutdown
// Address: 0x004a7810
// Role: Releases owned child object and transitions to a shut-down vtable state.
// Called from destructors and cleanup functions.

void __thiscall EARSObject::shutdown(EARSObject* this)
{
    // Switch vtable to active/operational vtable (PTR_FUN_00e353e0)
    this->vtable = &g_vtable_EARSObject_Active;  // +0x00

    // If child pointer (+0x0C) is non-null, perform intermediate cleanup
    if (this->m_pChild != 0) {
        EARSObject_cleanupChild();  // FUN_004a6400
    }

    // If child still exists, call its first virtual function (likely release/destructor) with argument 1
    if (this->m_pChild != 0) {
        this->m_pChild->vtable->release(this->m_pChild, 1);  // offset +0x00 in child vtable
    }

    // Final vtable change to shutdown/terminated state (PTR_LAB_00e2f638)
    this->vtable = &g_vtable_EARSObject_ShutDown;  // +0x00

    return;
}