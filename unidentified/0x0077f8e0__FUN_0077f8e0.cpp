// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(SomeClass *this, int param1, int param2, int param3)
{
  // +0x00: first field (likely a pointer or handle)
  this->field_0x00 = param1;
  // +0x10: initialized to 0
  this->field_0x10 = 0;
  // +0x0C: initialized to 0
  this->field_0x0C = 0;
  // +0x14: vtable or function pointer set to 0x0077f3b0
  this->field_0x14 = &LAB_0077f3b0;
  // +0x04: second parameter
  this->field_0x04 = param2;
  // +0x08: third parameter
  this->field_0x08 = param3;
}