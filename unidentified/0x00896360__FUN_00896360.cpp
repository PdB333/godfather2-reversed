// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = 0;              // +0x00: someInt1 = 0
  this[1] = 0;            // +0x04: someInt2 = 0
  this[2] = 0;            // +0x08: someInt3 = 0
  this[3] = 0;            // +0x0C: someInt4 = 0
  this[4] = 0;            // +0x10: someInt5 = 0
  this[5] = 1;            // +0x14: someBoolOrFlag = 1 (true)
  this[6] = 0;            // +0x18: someInt6 = 0
  this[7] = 0;            // +0x1C: someInt7 = 0
  this[8] = 0;            // +0x20: someInt8 = 0
  this[0x14] = 0xffffffff; // +0x50: someId = -1
  this[0x15] = 0xfe16702f; // +0x54: someMagicOrHash = 0xFE16702F
  this[0x16] = 2;          // +0x58: someEnumOrCount = 2
  this[0x15] = 0;          // +0x54: reset to 0 (overwrites previous value)
  return;
}