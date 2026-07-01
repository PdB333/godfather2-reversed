// FUNC_NAME: SomeClass::Constructor

void __fastcall SomeClass::Constructor(SomeClass *this)
{
    // Call base class constructor at 0x00855830
    BaseClass::BaseConstructor(this);
    // Set vtable pointer (offset +0x00)
    this->vtable = (void **)&someClassVtable;
}