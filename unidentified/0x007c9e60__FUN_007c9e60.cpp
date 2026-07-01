// FUNC_NAME: SomeClass::constructor
// Address: 0x007c9e60
// Role: Constructor with conditional initialization flag (bit 0 of param_2)
int __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor (FUN_007c8d80)
    baseConstructor(this);
    // If bit 0 of flags is set, call conditional cleanup/destructor (FUN_00624da0)
    if (flags & 1) {
        conditionalDestructor(this);
    }
    return reinterpret_cast<int>(this);
}