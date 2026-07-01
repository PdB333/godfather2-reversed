// FUNC_NAME: EARSObject::allocateResource
void __fastcall EARSObject::allocateResource(int thisPtr)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  // Call virtual function at offset +0x28 (likely resource allocator) with size 0x3c
  iVar1 = (**(code **)(**(int **)(thisPtr + 0x28) + 0x28))(0x3c, &local_c);
  if (iVar1 != 0) {
    // FUN_004c0250 likely initializes the allocated memory
    uVar2 = FUN_004c0250(local_4, unaff_retaddr, *(undefined4 *)(thisPtr + 0x28));
    *(undefined4 *)(thisPtr + 0x2c) = uVar2; // Store allocated resource handle at +0x2c
    return;
  }
  *(undefined4 *)(thisPtr + 0x2c) = 0; // Null handle on failure
  return;
}