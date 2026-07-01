// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int thisPtr)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Call base class constructor or initialization function
  FUN_005c1990();
  
  // Initialize member variables
  *(undefined4 *)(thisPtr + 0x58) = 5;          // +0x58: someCount = 5
  *(undefined4 *)(thisPtr + 0x5c) = 0xffffffff;  // +0x5c: someIndex = -1
  *(undefined4 *)(thisPtr + 0x60) = 0;           // +0x60: someFlag = 0
  *(undefined4 *)(thisPtr + 0x54) = 0xffffffff;  // +0x54: anotherIndex = -1
  *(undefined1 *)(thisPtr + 0x7c) = 0;           // +0x7c: someByte = 0
  
  // Initialize local structure and call another function
  local_c = DAT_01130310;  // Global data reference
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0);
  
  return;
}