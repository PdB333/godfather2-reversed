// FUNC_NAME: MeshVolatile::MeshVolatile
// Constructor for mesh volatile resource (streaming/transient mesh)
// This function initializes a MeshVolatile object, sets up its vtable and internal pointers,
// performs class registration via static initializers, and resets a global counter.
// 
// Offsets:
//   +0x00: vtable pointer (MeshVolatileVtbl*)
//   +0x04: (unknown, likely flags or reference count)
//   +0x08: secondary pointer (set twice: first to a base/static table, then to the final vtable/interface)
MeshVolatile * __thiscall MeshVolatile::MeshVolatile(MeshVolatile *this, uint8_t flags)
{
    // Set the primary vtable pointer
    this->vtable = (MeshVolatileVtbl*)&PTR_FUN_00e31b00;
    // Initialize secondary pointer to a base class or static data table
    this->field_08 = &PTR_LAB_00e31b0c;

    // Static class registration: first with a static descriptor (likely class metadata)
    FUN_0049c7f0(&DAT_00e31ae4);
    // Then with the class name string as a textual identifier
    FUN_0049c7f0("MeshVolatile");

    // Overwrite secondary pointer with the final vtable/interface table after base init
    this->field_08 = &PTR_LAB_00e31b10;

    // Reset global counter for MeshVolatile instances (e.g., tracking active objects)
    g_meshVolatileCount = 0;

    // Perform general initialization (e.g., register with resource manager, set defaults)
    FUN_0049c640();

    // If the object was heap-allocated (bit 0 of flags set), call custom cleanup / delete
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // likely a destructor or OP_DELETE-like function
    }

    return this;
}