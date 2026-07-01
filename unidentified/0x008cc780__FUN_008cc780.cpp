// FUNC_NAME: SomeClass::constructor
// Function address: 0x008cc780
// Role: Constructor for an unknown class, sets vtable and calls base constructor.

void __thiscall SomeClass::constructor(SomeClass *this)
{
    // Set vtable pointer to class-specific virtual table
    this->vtable = (void**)&VTable_0x00d7c520;
    
    // Call base class constructor at 0x4149b0
    // Likely initializes base class members
    BaseClass::constructor(this);
}