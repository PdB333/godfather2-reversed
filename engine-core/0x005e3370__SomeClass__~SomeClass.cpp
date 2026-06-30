// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(SomeClass *this, byte flags)

{
  // Set vtable to destroying vtable (base class destructor)
  *this = &PTR_FUN_00e3f50c;
  
  // Check if sub-object at offset +0x04 exists and call its virtual destructor
  if (this->field_0x04 != (int *)0x0) {
    (**(code **)(*this->field_0x04 + 0xc))(); // virtual destructor at offset +0x0c
  }
  
  // Set vtable to base class vtable
  *this = &PTR_LAB_00e3f510;
  
  // Reset global singleton flag
  DAT_01223518 = 0;
  
  // If flags bit 0 is set, delete this pointer (operator delete or placement delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete
  }
  
  return this;
}