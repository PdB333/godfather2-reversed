// FUNC_NAME: SomeClass::initializeFromParams
void __thiscall SomeClass::initializeFromParams(int thisPtr, undefined8 *param2, undefined8 *param3, undefined1 param4)
{
  undefined4 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  // Copy first 8 bytes from param2 to offset +0x4
  *(undefined8 *)(thisPtr + 4) = *param2;
  // Copy next 4 bytes from param2+1 to offset +0xC
  *(undefined4 *)(thisPtr + 0xc) = *(undefined4 *)(param2 + 1);
  // Copy first 8 bytes from param3 to offset +0x10
  *(undefined8 *)(thisPtr + 0x10) = *param3;
  uVar1 = DAT_00d813c8; // Global constant
  // Copy next 4 bytes from param3+1 to offset +0x18
  *(undefined4 *)(thisPtr + 0x18) = *(undefined4 *)(param3 + 1);
  // Store global constant at offset +0x28
  *(undefined4 *)(thisPtr + 0x28) = uVar1;
  // Store param4 at offset +0x50
  *(undefined1 *)(thisPtr + 0x50) = param4;
  // Initialize offset +0x1C to 0
  *(undefined4 *)(thisPtr + 0x1c) = 0;
  // Call some initialization function
  iVar3 = FUN_0078e110();
  if (iVar3 != 0) {
    // If successful, get some value and store at offset +0x51
    uVar2 = FUN_0078da20(1);
    *(undefined1 *)(thisPtr + 0x51) = uVar2;
  }
  return;
}