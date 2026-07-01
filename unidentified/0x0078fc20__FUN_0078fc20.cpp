// FUNC_NAME: SomeClass::initializeRandomSeed
void __thiscall SomeClass::initializeRandomSeed(int this, undefined4 param_2)
{
  int iVar1;
  uint uVar2;
  undefined1 local_14 [8];
  int local_c;
  int local_8;
  
  // Store the parameter at offset +0x98
  *(undefined4 *)(this + 0x98) = param_2;
  
  // Call sub-functions for initialization
  FUN_00791e70(this + 0x50);
  FUN_00790750(1);
  FUN_00790110(1);
  
  // Increment reference counts on global objects
  FUN_00408680(&DAT_012069c4);
  FUN_00408680(&DAT_0112db6c);
  
  // Set offset +0x9c to -1 (invalid)
  *(undefined4 *)(this + 0x9c) = 0xffffffff;
  
  iVar1 = 0;
  if (DAT_0112a53c != 0) {
    // Get current time/seed value
    FUN_00826510(local_14);
    iVar1 = local_8 + local_c * 0x3c;
  }
  
  // Call another function to process the seed
  iVar1 = FUN_0078fb20(iVar1);
  uVar2 = iVar1 + 1;
  
  // Clamp the value to the maximum allowed (stored at +0x94)
  if (*(uint *)(this + 0x94) <= uVar2) {
    uVar2 = 0xffffffff;
  }
  
  // Store the result at +0xa0
  *(uint *)(this + 0xa0) = uVar2;
  
  // If invalid, set to 0
  if (uVar2 == 0xffffffff) {
    *(undefined4 *)(this + 0xa0) = 0;
  }
  
  return;
}