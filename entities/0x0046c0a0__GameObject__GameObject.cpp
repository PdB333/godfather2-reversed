// FUNC_NAME: GameObject::GameObject

// 0x0046c0a0 - Constructor for GameObject (derived from EARSBase)
// Sets vtable to base, calls base constructor, then sets final vtable.
// If the `flags` low bit is set, calls operator delete on the object
// (common EA engine pattern for preventing double deletion or placement delete).

__thiscall GameObject *GameObject::GameObject(GameObject *this, uint8_t flags) {
    // Set vtable to base class vtable (EARSBase)
    this->vtable = (void *)&g_pEARSBaseVtable; // 0x00e327d8

    // Call base class constructor
    EARSBase::EARSBase((EARSBase *)this); // 0x0043e380

    // Set vtable to derived class vtable (GameObject)
    this->vtable = (void *)&g_pGameObjectVtable; // 0x00e30ea0

    // If the placement-allocation flag is set, delete the raw memory
    // (used when the object was created via `new` and cleanup is needed)
    if ((flags & 1) != 0) {
        operator delete(this); // 0x009c8eb0
    }

    return this;
}