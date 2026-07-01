// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *this)
{
  this[1] = 0; // +0x04: some field, likely a counter or flag
  FUN_009c8f10(this[0]); // +0x00: call to a function with the first field as argument
  this[0] = 0; // +0x00: reset first field to 0
  this[2] = 0; // +0x08: another field reset to 0
  return;
}