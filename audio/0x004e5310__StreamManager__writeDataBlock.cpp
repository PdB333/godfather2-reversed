// FUNC_NAME: StreamManager::writeDataBlock
void __thiscall StreamManager::writeDataBlock(int *param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9, undefined4 param_10, undefined4 param_11)
{
  int *piVar1;
  int iVar2;
  void *_Dst;
  undefined8 *puVar3;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar2 = *param_1;
  // +0x14: current write pointer in stream buffer
  **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_01124a90;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  local_24 = param_3;
  local_20 = param_4;
  local_1c = param_5;
  iVar2 = *param_1;
  local_18 = param_6;
  local_14 = param_7;
  local_10 = param_8;
  local_c = param_9;
  // Write the type/ID (param_2) at current position
  **(undefined4 **)(iVar2 + 0x14) = param_2;
  // Align to 4-byte boundary after writing the ID
  _Dst = (void *)(*(int *)(iVar2 + 0x14) + 7U & 0xfffffffc);
  *(void **)(iVar2 + 0x14) = _Dst;
  // Copy the data block (7 dwords = 28 bytes = 0x1c) from local_24
  _memcpy(_Dst,&local_24,0x1c);
  // Align to 8-byte boundary after data block
  puVar3 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0x1fU & 0xfffffffc);
  *(undefined8 **)(iVar2 + 0x14) = puVar3;
  // Write the final 8-byte value (param_10, param_11 concatenated)
  *puVar3 = CONCAT44(param_11,param_10);
  // Advance write pointer past the final value
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 8;
  return;
}