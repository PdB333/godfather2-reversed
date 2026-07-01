// FUNC_NAME: EARSStream::writeDataBlock
void __thiscall EARSStream::writeDataBlock(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
{
  int *piVar1;
  int iVar2;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = *this;
  // Write pointer to vtable or function table at offset +0x14
  **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_00e56988;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  
  iVar2 = *this;
  local_10 = param_3;
  local_c = param_4;
  local_8 = param_5;
  local_4 = param_6;
  // Write param_2 to the stream buffer at offset +0x14
  **(undefined4 **)(iVar2 + 0x14) = param_2;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  
  // Copy 16 bytes (0x10) from local stack to stream, 4 bytes at a time
  FUN_0049c430(&local_10, 0x10, 4);
  return;
}