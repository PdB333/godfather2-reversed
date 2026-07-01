// FUNC_NAME: UnknownClass::constructorWithFlag
// This function appears to be a constructor that calls a base constructor (FUN_007c0910)
// and optionally performs cleanup (FUN_00624da0) if bit 0 of param_2 is set.
// Possibly used for placement new with optional destruction.
// Returns this pointer.

undefined4 __thiscall SomeClass::constructorWithFlag(SomeClass* this, byte flag)
{
    SomeClass::baseConstructor(this);  // FUN_007c0910 - likely base class constructor
    if ((flag & 1) != 0) {
        SomeClass::destructorOrDealloc(this);  // FUN_00624da0 - clean up
    }
    return this;  // Return this pointer (even if destructor called? unusual)
}