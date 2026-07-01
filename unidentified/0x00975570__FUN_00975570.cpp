// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00975570
// Constructor that calls base class initialization and optionally performs additional setup based on a flag.

undefined4 __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Call base class constructor or initialization
    BaseClass::BaseClass(this);  // FUN_00974fa0

    // If the flag's lowest bit is set, perform additional initialization
    if ((flag & 1) != 0)
    {
        SomeClass::additionalInit(this);  // FUN_005c4480
    }

    return this;
}