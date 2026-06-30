// FUNC_NAME: MemoryPool::allocateNode
void MemoryPool::allocateNode(void)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = DAT_012224ec;
  if (DAT_012224ec == (undefined4 *)0x0) {
    puVar1 = &DAT_01218a14;
  }
  puVar2 = (undefined4 *)(**(code **)*DAT_012224f0)(0xc);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = *puVar1;
    puVar2[2] = 0;
    puVar2[1] = 0;
  }
  if (DAT_012224e4 != (undefined4 *)0x0) {
    *(undefined4 **)((int)DAT_012224e4 + 4) = puVar2;
    *(undefined4 **)(*(int *)((int)DAT_012224e4 + 4) + 8) = DAT_012224e4;
    DAT_012224e8 = DAT_012224e8 + 1;
    DAT_012224e4 = (undefined4 *)*(undefined4 *)((int)DAT_012224e4 + 4);
    return;
  }
  DAT_012224e8 = DAT_012224e8 + 1;
  DAT_012224e0 = puVar2;
  DAT_012224e4 = puVar2;
  return;
}