// FUNC_NAME: DerivedClass::constructor
// 0046bba0: Constructor for a derived class. Sets vtable to base class, calls base constructor, then updates to derived vtable.
void __fastcall DerivedClass::constructor(DerivedClass* this)
{
    // Set vtable pointer to base class vtable (at 0x00e32768)
    this->vtable = (void*)0x00e32768;
    // Call base class constructor
    BaseClass::constructor(this);
    // Update vtable pointer to derived class vtable (at 0x00e30ea0)
    this->vtable = (void*)0x00e30ea0;
    return;
}