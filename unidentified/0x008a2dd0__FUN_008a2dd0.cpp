// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6)
{
  // +0x00: first field
  *this = param2;
  // +0x0C: fourth field (3 * 4)
  this[3] = param5;
  // +0x04: second field
  this[1] = param3;
  // +0x08: third field
  this[2] = param4;
  // +0x10: fifth field, initialized to 2 (likely an enum or type)
  this[4] = 2;
  // +0x14: sixth field, zeroed
  this[5] = 0;
  // +0x18: seventh field, zeroed
  this[6] = 0;
  // +0x1C: eighth field
  this[7] = param6;
  // +0x20: start of a 0x30-byte buffer, zeroed out (likely an array or sub-struct)
  _memset(this + 8, 0, 0x30);
  return this;
}