// FUNC_NAME: SomeClass::constructor
// Address: 0x0090d060
// This function is a constructor that takes a flag indicating whether to deallocate on failure.
// It calls base initialization and conditionally calls a deallocation function.

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flag)
{
    // Call base class constructor or initialization
    FUN_0090cca0(this);  // likely base constructor
    if ((flag & 1) != 0) {
        // If flag bit 0 is set, call deallocation (operator delete or destructor)
        FUN_009c8eb0(this);
    }
    return this;
}