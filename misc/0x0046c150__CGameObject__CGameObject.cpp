// FUNC_NAME: CGameObject::CGameObject
CGameObject* __thiscall CGameObject::CGameObject(CGameObject* this, byte allocFlag) {
    // Set base class vtable (EARSObject)
    this->vtable = (void*)&EARSObject_vtable; // PTR_FUN_00e327e4
    // Call base class constructor
    EARSObject::EARSObject(this); // FUN_0043e380

    // Set derived class vtable
    this->vtable = (void*)&CGameObject_vtable; // PTR_LAB_00e30ea0

    // If heap-allocated (allocFlag & 1), call registration/cleanup function
    if ((allocFlag & 1) != 0) {
        // Likely registers object in heap-allocated tracking list or fires post-alloc callback
        // (FUN_009c8eb0) may be a placement delete guard or registration helper
        FUN_009c8eb0(this);
    }

    return this;
}