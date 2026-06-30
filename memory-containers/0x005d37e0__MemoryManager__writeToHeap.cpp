// FUNC_NAME: MemoryManager::writeToHeap
void __thiscall MemoryManager::writeToHeap(void *this, void *src, uint size)
{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *_Dst;
  uint local_1c;
  undefined1 local_18 [16];
  size_t sStack_8;
  
  puVar2 = (undefined4 *)FUN_0060b620(size,0,0,0x12);
  uVar1 = (uint)this;
  local_1c = (uint)this;
  if ((_DAT_01225e2c & 1) == 0) {
    _DAT_01225e2c = _DAT_01225e2c | 1;
    _DAT_01225e10 = &PTR_FUN_00e36cb4;
    FUN_004cfc30(0x200);
    _atexit((_func_4879 *)&LAB_00d51130);
  }
  this = puVar2;
  FUN_00423cf0(&local_1c,&this,uVar1 % DAT_01225e18);
  if (*(char *)(puVar2 + 7) == '\0') {
    _Dst = (undefined4 *)puVar2[4];
    *(undefined1 *)((int)puVar2 + 0x1d) = 1;
  }
  else {
    uVar3 = 0;
    this = (undefined4 *)0x0;
    if (*(char *)(puVar2 + 3) != '\0') {
      uVar3 = 0x3000;
    }
    (**(code **)(*(int *)*puVar2 + 0x2c))((int *)*puVar2,0,0,&this,uVar3);
    _Dst = this;
  }
  if (*(char *)(puVar2 + 7) == '\0') {
    sStack_8 = puVar2[5];
  }
  else {
    (**(code **)(*(int *)*puVar2 + 0x34))((int *)*puVar2,local_18);
  }
  _memcpy(_Dst,src,sStack_8);
  if (*(char *)(puVar2 + 7) != '\0') {
    (**(code **)(*(int *)*puVar2 + 0x30))((int *)*puVar2);
    return;
  }
  *(undefined1 *)((int)puVar2 + 0x1d) = 0;
  return;
}