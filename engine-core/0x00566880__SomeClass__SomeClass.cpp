// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00566880
// Role: Constructor for SomeClass (with optional initialization flag)

// The class is unknown; naming as SomeClass for illustration.
// In the EA EARS engine, many constructors use a byte flag to control initialization
// (e.g., bit 0 triggers additional setup or memory allocation).

SomeClass* __thiscall SomeClass::SomeClass(byte initFlag)
{
    // Call base class or global initialization routine (likely a base constructor or global state update)
    FUN_00b0fa90();

    // If the low bit of initFlag is set, perform extra initialization on this instance
    if ((initFlag & 1) != 0) {
        FUN_009c8eb0(this);  // Additional constructor steps (e.g., copy, allocate resources)
    }

    return this;
}