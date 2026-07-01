// FUNC_NAME: SomeClass::initializeSomething
void __fastcall SomeClass::initializeSomething(int thisPtr)
{
  int iVar1;
  
  if (thisPtr == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thisPtr + 0x10;
  }
  // Call function with a label and flag
  FUN_005c02f0(iVar1, &LAB_00933670, 1);
  // Reset some global state
  FUN_00983120(0, 0, 0);
  // Set a global flag to 0x20
  DAT_00e5672c = 0x20;
  // Clear field at offset +0x60
  *(undefined4 *)(thisPtr + 0x60) = 0;
  // Check if a global flag bit 0 is not set
  if ((DAT_01130590 & 1) == 0) {
    // Call another function with offset +0x14 and a label
    FUN_005c0d50(thisPtr + 0x14, &LAB_00931e00, 0);
    // Set the global flag bit 0
    DAT_01130590 = DAT_01130590 | 1;
  }
  return;
}