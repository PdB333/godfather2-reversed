// FUNC_NAME: Entity::Entity
// Address: 0x007edfb0
// Reconstructed constructor for EARS Entity base class.
// Sets vtable pointer, performs global initialization, initializes sub-object at offset 0x1C,
// and calls post-construction step.

void __thiscall Entity::Entity(Entity* this)
{
    // Assign vtable pointer (static table at 0x00d70000)
    this->vtable = &Entity_vtable;

    // Global reference count / lock increment (uses global at 0x012069c4)
    globalEntityLock(&DAT_012069c4);

    // Initialize child object at offset 0x1C (param_1[7])
    // This likely releases previous content or performs placement construction.
    initializeChildObject(this->field_0x1C);

    // Finalize construction (e.g. register with manager, update counters)
    finalizeConstruction();
}