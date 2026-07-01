// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *this)
{
  this[1] = 0;          // +0x04: some field (e.g., state, count, or pointer)
  FUN_009c8f10(this[0]); // call with first field (likely a handle or pointer)
  this[0] = 0;          // +0x00: reset first field to null/zero
  this[2] = 0;          // +0x08: another field reset
  return;
}