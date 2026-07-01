// FUNC_NAME: SomeGameObject::constructor

void __fastcall SomeGameObject::constructor(SomeGameObject *this)
{
  // Set primary vtable pointer at offset 0x00
  this->vtable = (void **)0xd738e0;

  // Call base class constructor (likely sets its own vtable)
  SomeBaseClass::constructor();

  // Set secondary vtable pointer at offset 0x30 (index 0xc * 4)
  this->secondaryVtable = (void **)0xe32854;

  // Call additional initialization function
  SomeInitializationFunction();
}