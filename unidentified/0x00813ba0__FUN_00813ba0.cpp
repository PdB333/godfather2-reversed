// FUNC_NAME: SomeClass::constructor (or destructor with delete flag)
int __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor at 0x00813960
    this->baseConstructor(); // FUN_00813960

    // If bit 0 is set, deallocate memory (size 0x78)
    if (flags & 1)
    {
        // FUN_0043b960: likely operator delete with size hint 0x78
        operator delete(this, 0x78);
    }

    // Return this pointer (common for constructors)
    return (int)this;
}