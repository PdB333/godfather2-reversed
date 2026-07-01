// FUNC_NAME: EARS::Framework::Entity::Entity (constructor)
// Constructor for an EARS engine entity with multiple virtual table pointers.
// Sets up the object's vtable, secondary interfaces, initializes subsystems,
// and conditionally registers for cleanup if the allocation flag is set.

Entity* __thiscall Entity::Entity(Entity* this, byte allocFlags)
{
    // Set primary vtable at offset 0x00
    this->vtable = &g_EntityVTable;                                  // PTR_FUN_00d915d8

    // Set secondary vtable for base class or interface at +0x04
    *(void**)((uintptr)this + 4) = &g_BaseVTable;                   // PTR_LAB_00d915b0

    // Set tertiary vtable (possibly for IRuntimeType) at +0x13 (19)
    *(void**)((uintptr)this + 0x13) = &g_Interface1VTable;         // PTR_LAB_00d915ac

    // Set quaternary vtable at +0x1d (29)
    *(void**)((uintptr)this + 0x1d) = &g_Interface2VTable;         // PTR_LAB_00d83b18

    // Call base class constructor (likely parent's init)
    baseEntityInit();                                               // FUN_00407430

    // Replace tertiary vtable with a derived version (polymorphic override)
    *(void**)((uintptr)this + 0x13) = &g_Interface1DerivedVTable; // PTR_LAB_00d91594

    // Clear global flag (e.g., singleton creation guard)
    g_entityGlobalFlag = 0;                                          // DAT_0112992c

    // Initialize core subsystems (e.g., networking, input)
    initializeSubsystems();                                          // FUN_005c16e0

    // If the object was heap-allocated (bit 0 set), call cleanup
    if (allocFlags & 1)
    {
        finalizeConstruction(this);                                  // FUN_005c4480
    }

    return this;
}