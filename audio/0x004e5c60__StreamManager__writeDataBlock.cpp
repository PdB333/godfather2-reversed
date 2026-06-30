// FUNC_NAME: StreamManager::writeDataBlock
void __thiscall StreamManager::writeDataBlock(int *this, undefined4 param_2, void *param_3)
{
  int *piVar1;
  int iVar2;
  void *_Dst;
  
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01124b44;  // +0x14: current write pointer
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;  // advance past pointer
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = param_2;  // write block type/size
  _Dst = (void *)(*(int *)(iVar2 + 0x14) + 0x13U & 0xfffffff0);  // align to 16 bytes
  *(void **)(iVar2 + 0x14) = _Dst;
  _memcpy(_Dst,param_3,0x20);  // copy 32 bytes of data
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 0x20;  // advance past data
  return;
}