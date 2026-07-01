// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(int thisPtr)
{
  // Set some flag at offset +0x18C (bit 13 set) - likely a status/state flag
  *(uint *)(thisPtr + 0x18C) |= 0x2000;
  
  // Call some initialization/reset functions
  FUN_008b9050(0);
  FUN_004df590();
  
  // Initialize a sub-object at offset +0x1B4 with zero values
  FUN_008b9e20(thisPtr + 0x1B4, 0, 0);
}