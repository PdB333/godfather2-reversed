// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(SomeClass *this, int param_2, int param_3)
{
  this->field_0 = param_2;      // +0x00
  this->field_4 = param_3;      // +0x04
  this->field_8 = 0;            // +0x08
  *(byte *)(this + 0x0C) = 0;   // +0x0C (byte field)
  this->field_10 = 0;           // +0x10
  this->field_14 = 0;           // +0x14
  this->field_18 = 0;           // +0x18
  return;
}