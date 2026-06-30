// FUNC_NAME: RingBuffer::pushBack
void __thiscall RingBuffer_pushBack(void *this, undefined8 *param_1)
{
  uint uVar1;
  undefined8 *puVar2;
  uint uVar3;
  int unaff_ESI;
  undefined1 local_8 [8];
  
  uVar1 = *(uint *)(unaff_ESI + 8);
  if ((uVar1 != 0) &&
     ((uint)((int)(*(int *)(unaff_ESI + 0xc) - uVar1) / 0x28) <
      (uint)((int)(*(int *)(unaff_ESI + 0x10) - uVar1) / 0x28))) {
    puVar2 = *(undefined8 **)(unaff_ESI + 0xc);
    if (puVar2 != (undefined8 *)0x0) {
      *puVar2 = *param_1;
      puVar2[1] = param_1[1];
      puVar2[2] = param_1[2];
      puVar2[3] = param_1[3];
      puVar2[4] = param_1[4];
    }
    *(undefined8 **)(unaff_ESI + 0xc) = puVar2 + 5;
    return;
  }
  uVar3 = *(uint *)(unaff_ESI + 0xc);
  if (uVar3 < uVar1) {
    FUN_00b97aea();
  }
  FUN_005d9d40(local_8,unaff_ESI,uVar3,param_1);
  return;
}