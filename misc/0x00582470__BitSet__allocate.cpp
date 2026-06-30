// FUNC_NAME: BitSet::allocate
undefined4 * BitSet::allocate(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *unaff_ESI;
  undefined4 *puVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  uVar1 = (**(code **)*unaff_ESI)((param_1 + 0x1f >> 5) * 4,&local_c);
  local_c = 0;
  puVar2 = (undefined4 *)(**(code **)*unaff_ESI)(8,&stack0xffffffec);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    *puVar2 = uVar1;
    puVar2[1] = param_1;
  }
  puVar4 = (undefined4 *)*puVar2;
  if (puVar4 < puVar4 + (puVar2[1] + 0x1f >> 5)) {
    iVar3 = ((uint)((int)(puVar4 + (puVar2[1] + 0x1f >> 5)) + (-1 - (int)puVar4)) >> 2) + 1;
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  return puVar2;
}