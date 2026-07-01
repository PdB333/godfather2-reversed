// FUNC_NAME: Gun::constructor
undefined4 * __thiscall Gun::constructor(Gun *this, undefined4 param_2)

{
  FUN_0046c590(param_2);
  this->vtable = &PTR_FUN_00d83240;
  this->field_0x3c = &PTR_LAB_00d83230; // +0x3C vtable or function pointer
  this->field_0x48 = &PTR_LAB_00d8322c; // +0x48 vtable or function pointer
  this->field_0x50 = 0; // +0x50 some flag/pointer
  *(undefined2 *)(&this->field_0x54) = 0; // +0x54 (16-bit field)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (16-bit field)
  this->field_0x64 = 0; // +0x64 some pointer/flag
  this->field_0x60 = 0; // +0x60 some pointer/flag
  this->field_0x5c = 0; // +0x5C some pointer/flag
  this->field_0x58 = 0; // +0x58 some pointer/flag
  this->field_0x6c = 0; // +0x6C some pointer/flag
  this->field_0x68 = 3; // +0x68 some count/enum (default 3)
  this->field_0x70 = 0; // +0x70 some pointer/flag
  return this;
}