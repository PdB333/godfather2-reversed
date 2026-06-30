// FUN_006f31e0: DerivedClass::DerivedClass (constructor)
// Address: 0x006F31E0
// Calls base constructor and optionally allocates memory (size 0x114) if param_2 bit 0 is set

void __thiscall DerivedClass::DerivedClass(byte allocFlag)
{
    BaseClass::BaseClass();                       // Base constructor
    if ((allocFlag & 1) != 0) {
        allocateMemory(this, 0x114);              // Allocate 0x114 bytes for this object (custom allocator)
    }
    return;                                       // implicit return of `this`
}