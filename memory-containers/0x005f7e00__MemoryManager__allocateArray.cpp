// FUNC_NAME: MemoryManager::allocateArray
void * __fastcall MemoryManager::allocateArray(int param_1)
{
  int iVar1;
  int *in_EAX;
  void *_Dst;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = *in_EAX;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  _Dst = (void *)(**(code **)**(undefined4 **)(param_1 + 0x10))(iVar1 * 0xc,&local_c);
  _memset(_Dst,0,iVar1 * 0xc);
  return _Dst;
}