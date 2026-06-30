// FUNC_NAME: SomeClass::constructorWithFlag

undefined4* __thiscall SomeClass::constructorWithFlag(SomeClass* this, byte flags)
{
    // Set vtable pointer to class-specific vtable
    this->vtable = &PTR_FUN_00d587e0;

    // Call base class constructor (e.g., EARSObject constructor)
    baseClassConstructor();

    // If the low bit of flags is set, call a destructor-like function
    // This likely handles cleanup or specific memory management
    if (flags & 1) {
        operatorDelete(this); // Placement delete or object destructor
    }

    return this;
}