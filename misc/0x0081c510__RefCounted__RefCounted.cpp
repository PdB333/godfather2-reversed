// FUNC_NAME: RefCounted::RefCounted
undefined4 * __thiscall RefCounted::RefCounted(RefCounted *this, int *vtable, int copySource) {
    // This constructor initializes a reference-counted object.
    // vtable: pointer to virtual function table for the object's type.
    // copySource: optional pointer to an existing object (if non-zero, clone it).
    // +0x00: vtable pointer (this->vtable)
    // +0x04: pointer to owned/cloned object (this->ownedObject)

    this->vtable = vtable;
    // Call virtual function at vtable[2] (offset 0x08) – likely early initialization (e.g., reset refcount)
    (this->vtable[2])();

    if (copySource != 0) {
        // Clone the object pointed to by copySource using a type-specific factory
        this->ownedObject = FUN_004265d0(copySource, this->vtable);
        // Call virtual function at vtable[1] (offset 0x04) – likely release original copySource (e.g., decrement refcount)
        (this->vtable[1])(copySource, 0);
        // Call virtual function at vtable[3] (offset 0x0C) – final initialization (e.g., post-construct)
        (this->vtable[3])();
        return this;
    }

    this->ownedObject = 0;
    (this->vtable[3])();
    return this;
}