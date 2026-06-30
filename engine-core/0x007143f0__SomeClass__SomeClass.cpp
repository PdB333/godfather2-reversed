// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x007143f0
// Role: Constructor for SomeClass, with optional memory management based on allocFlag.
// Calls base class initializer (FUN_00713650) and conditionally invokes cleanup/destroy (FUN_009c8eb0).

int __thiscall SomeClass::SomeClass(SomeClass* this, byte allocFlag)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    BaseClass::BaseClass(this);  // FUN_00713650

    // If allocFlag bit 0 is set, perform cleanup or destruction (e.g., free heap memory)
    // This pattern is common in EA EARS engine for constructors that can be used
    // with placement new (allocFlag=0) or dynamic allocation (allocFlag=1).
    if ((allocFlag & 1) != 0)
    {
        SomeClass::cleanup(this);  // FUN_009c8eb0
    }

    return this;
}