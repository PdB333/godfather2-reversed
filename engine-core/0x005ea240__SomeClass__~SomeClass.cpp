// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(SomeClass *this, byte flags)
{
  // Set vtable to derived class vtable (PTR_FUN_00e36f1c)
  this->vtable = &PTR_FUN_00e36f1c;

  // If the member at offset +0x4 is non-null, call its virtual function at offset 0xc (likely release/destructor)
  if (this->field_0x4 != (int *)0x0) {
    (**(code **)(*this->field_0x4 + 0xc))();
  }

  // Set vtable to base class vtable (PTR_LAB_00e362b8) – possibly to prevent further virtual calls
  this->vtable = &PTR_LAB_00e362b8;

  // If flags bit 0 is set, deallocate memory via FUN_009c8eb0 (likely operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}