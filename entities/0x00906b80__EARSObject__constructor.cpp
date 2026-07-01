// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *this)
{
  this[1] = 0; // +0x04: some flag or pointer, initialized to null
  FUN_009c8f10(this[0]); // likely initializes base class or subsystem
  this[0] = 0; // +0x00: vtable or self pointer, cleared after init
  this[2] = 0; // +0x08: another member, initialized to null
  return;
}