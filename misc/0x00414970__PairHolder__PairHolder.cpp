// FUNC_NAME: PairHolder::PairHolder
void __thiscall PairHolder::PairHolder(PairHolder* this, uint param_2, uint param_3)
{
  // Structure: +0x00 vtable ptr, +0x04 value1, +0x08 value2
  this->vtable = &PTR_LAB_00e2f5c0; // VTable pointer at offset 0x00
  this->value1 = param_2; // Store first parameter at +0x04
  this->value2 = param_3; // Store second parameter at +0x08
  return;
}