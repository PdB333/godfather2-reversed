// FUNC_NAME: UnknownClass::clearOrReset
void __fastcall UnknownClass::clearOrReset(undefined4 *this)
{
  this[1] = 0;              // +0x04: some member variable (e.g. flags, count, or pointer)
  FUN_009c8f10(*this);      // call with this[0] (likely ID, handle, or pointer)
  *this = 0;                // +0x00: reset the first field to null/0
  this[2] = 0;              // +0x08: reset the third field to null/0
}