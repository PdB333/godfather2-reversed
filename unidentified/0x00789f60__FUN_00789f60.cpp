// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00789f60
// Role: Constructor for SomeClass. Calls base initialization, then conditionally performs additional setup based on a flag.

// __thiscall: this pointer in ECX, flag in a register (byte)
SomeClass* __thiscall SomeClass::SomeClass(byte flag)
{
    // Call base class constructor or common initialization routine
    baseInit();

    // If the low bit of flag is set, perform additional initialization
    if ((flag & 1) != 0) {
        additionalInit(this);
    }

    // Return this pointer (standard constructor convention)
    return this;
}