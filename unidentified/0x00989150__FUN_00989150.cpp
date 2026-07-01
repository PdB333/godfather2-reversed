// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int *this)
{
  code *vtableEntry;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;

  local_c = DAT_01130310; // Some global data
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0); // Likely a string/object initialization
  vtableEntry = *(code **)(*this + 0x2c); // Get vtable entry at offset 0x2c
  *(undefined1 *)((int)this + 0x58) = 0; // Set byte at this+0x58 to 0 (some flag)
  (*vtableEntry)(); // Call virtual function via vtable
  return;
}