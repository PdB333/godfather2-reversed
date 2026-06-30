// FUNC_NAME: EARSAllocator::pushData
void __thiscall EARSAllocator::pushData(int *this, undefined4 param_2, void *param_3)
{
  int *piVar1;
  int iVar2;
  void *_Dst;
  
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01124b58;  // +0x14: current write pointer
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = param_2;  // store type/ID
  _Dst = (void *)((*(int *)(iVar2 + 0x14) + 0x13U) & 0xfffffff0);  // align to 16 bytes
  *(void **)(iVar2 + 0x14) = _Dst;
  _memcpy(_Dst, param_3, 0x30);  // copy 48 bytes of data
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 0x30;  // advance write pointer
  return;
}