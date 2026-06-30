// FUNC_NAME: SomeGameObject::Constructor
undefined4 * __thiscall SomeGameObject::Constructor(SomeGameObject *this, byte allocFlag)
{
    // Set base class vtable (likely EARSObject or similar)
    this->vtable = &PTR_FUN_00d60690;

    // Initialize four sub-components (e.g., network slots, animation states, etc.)
    this->initComponent();  // +0x04? 
    this->initComponent();  // +0x08?
    this->initComponent();  // +0x0C?
    this->initComponent();  // +0x10?

    // Override vtable to derived class vtable
    this->vtable = &PTR_FUN_00d587e0;

    // Derived class-specific initialization (e.g., setup pointers, load data)
    this->initializeSpecific();

    // If the object was heap-allocated (e.g., via new), free memory?
    // This is unusual; possibly a debug or fail-safe deletion.
    if (allocFlag & 1) {
        operatorDelete(this);
    }

    return this;
}