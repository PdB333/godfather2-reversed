// FUNC_NAME: Entity::Entity
// Function address: 0x00564010
// Role: Constructor for an Entity object with two vtable pointers (multiple inheritance).
//       The second vtable is at offset +0x4. If construction flags bit0 is set, performs
//       additional TLS-based initialization (likely custom allocator for small objects).

__thiscall Entity::Entity(Entity* this, byte flags)
{
    // Set vtable pointers for base classes (multiple inheritance layout)
    if (this != NULL) {
        this->vtable2 = (void*)&PTR_LAB_00d987cc; // second vtable at +4
    } else {
        // NB: This path writes to NULL – likely never called in practice.
        *(uint32*)NULL = (uint32)&PTR_LAB_00d987cc;
    }
    this->vtable1 = (void*)&PTR_LAB_00d96914; // first vtable at +0

    // Optional construction: TLS allocator setup
    if ((flags & 1) != 0) {
        // Retrieve thread-local storage value (allocation context)
        TlsGetValue(DAT_01139810);
        // Call custom allocator/initializer for object of size 0x27 (39 bytes)
        // The second argument is the low 16 bits from *(uint16*)(this + 4) (likely small ID)
        FUN_00aa26e0(this, *(uint16*)((byte*)this + 4), 0x27);
    }
    return this;
}