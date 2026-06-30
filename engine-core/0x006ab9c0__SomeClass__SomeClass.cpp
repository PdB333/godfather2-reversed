// FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(byte initializeFlags)
{
    // Call base class constructor (likely EARS base object)
    BaseClass::constructor();

    // Zero-initialize the entire object (size 0x9C = 156 bytes) if the LSB is set
    if ((initializeFlags & 1) != 0) {
        IceMemory::zeroFill(this, 0x9C); // or memset(this, 0, 0x9C)
    }

    return (undefined4)this;
}