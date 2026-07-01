// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046c590(param_2);
  *this = &PTR_FUN_00d7cae8;
  this[0xf] = &PTR_LAB_00d7cad8;
  this[0x12] = &PTR_LAB_00d7cad4;
  *(undefined2 *)(this + 0x15) = 0;
  *(undefined2 *)((int)this + 0x56) = 0;
  this[0x16] = 0xbadbadba;
  this[0x17] = 0xbeefbeef;
  this[0x18] = 0xeac15a55;
  this[0x19] = 0x91100911;
  this[0x1a] = 0;
  this[0x14] = 0;
  return this;
}