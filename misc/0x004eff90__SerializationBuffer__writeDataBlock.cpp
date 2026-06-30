// FUNC_NAME: SerializationBuffer::writeDataBlock
void __thiscall SerializationBuffer::writeDataBlock(int *param_1, undefined4 param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5, undefined8 param_6)
{
  int *piVar1;
  int iVar2;
  void *_Dst;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  iVar2 = *param_1;
  // Write vtable pointer (function table entry)
  **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_01124cec;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  
  iVar2 = *param_1;
  // Write the type/ID parameter
  **(undefined4 **)(iVar2 + 0x14) = param_2;
  
  // Copy the 32-byte data block (param_3 through param_6)
  local_20 = param_3;
  local_18 = param_4;
  // Align destination pointer to 4-byte boundary
  _Dst = (void *)(*(int *)(iVar2 + 0x14) + 7U & 0xfffffffc);
  local_10 = param_5;
  local_8 = param_6;
  *(void **)(iVar2 + 0x14) = _Dst;
  _memcpy(_Dst, &local_20, 0x20);  // Copy 32 bytes of data
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 0x20;  // Advance buffer pointer
  return;
}