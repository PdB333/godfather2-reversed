// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00881110
// Role: Constructor for SomeClass. Calls base initialization and optionally performs cleanup if flag bit 0 is set.

SomeClass* __thiscall SomeClass::SomeClass(byte flag)
{
    this->initializeBase(); // FUN_00881050 - base class initialization
    if ((flag & 1) != 0) {
        this->destroy(); // FUN_00624da0 - cleanup/destructor call
    }
    return this;
}