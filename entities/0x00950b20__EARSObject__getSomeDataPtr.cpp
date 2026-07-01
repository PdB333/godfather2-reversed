// FUNC_NAME: EARSObject::getSomeDataPtr
int __fastcall EARSObject::getSomeDataPtr(int thisPtr)
{
  int result;
  
  // Check if bit 0 of +0x58 is set (some flag)
  if ((*(byte *)(thisPtr + 0x58) & 1) != 0) {
    // If flag is set, try another branch
    result = FUN_00950a40(); // likely a virtual method or helper
    if (result != 0) {
      FUN_00950a40();
      result = FUN_00791300(); // some global function
      if (result != 0) goto LAB_00950b47;
    }
    return thisPtr + 0x158; // offset to a member
  }
  
  // If bit 0 is not set
  result = FUN_00950a40();
  if (result == 0) {
    // Try another path
    result = FUN_009506e0(); // likely another helper
    if (result != 0) {
      result = FUN_009506e0();
      return result + 0x10; // offset into some object
    }
    return 0;
  }
  
  // If result was non-zero
  FUN_00950a40();
  result = FUN_00791300();
  if (result == 0) {
    FUN_00950a40();
    result = FUN_00790cd0();
    return result;
  }
  
LAB_00950b47:
  result = FUN_00471610(); // some global function
  return result + 0x30; // offset into some object
}