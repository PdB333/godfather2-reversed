// FUNC_NAME: MaterialSwapListResource::MaterialSwapListResource

// Constructor for MaterialSwapListResource class.
// Sets up vtable, registers resource type, initializes global counter.
// param_2: flag indicating whether to call deallocation on failure (bit 0).

extern int g_materialSwapListResourceCount; // DAT_01129998

void * __thiscall MaterialSwapListResource::MaterialSwapListResource(MaterialSwapListResource *this, byte flag)
{
    // Set vtable pointer (first virtual function table)
    this->vtable = &PTR_FUN_00d77720; // +0x00: vtable pointer

    // Set secondary vtable pointer (possibly base class or interface)
    this->field_0x08 = &PTR_LAB_00d7771c; // +0x08: secondary vtable

    // Register this resource type with the resource manager
    registerResourceType("MaterialSwapListResource"); // FUN_0049c7f0

    // Update secondary vtable pointer after registration
    this->field_0x08 = &PTR_LAB_00d77718; // +0x08: updated secondary vtable

    // Reset global resource count
    g_materialSwapListResourceCount = 0; // DAT_01129998

    // Call base initialization
    initializeResource(); // FUN_0049c640

    // If flag bit 0 is set, deallocate memory (e.g., for placement new failure)
    if ((flag & 1) != 0) {
        deallocateMemory(this); // FUN_009c8eb0
    }

    return this;
}