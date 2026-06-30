// FUNC_NAME: ObjectPool::allocateObject
int __thiscall ObjectPool::allocateObject(int thisPtr, int *param2, int *param3, undefined4 param4, int param5, undefined4 param6, undefined4 param7, undefined4 param8)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int unaff_EBX;
  int iVar7;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  piVar3 = param2;
  if (*param2 == 0) {
    param2 = (int *)0x0;
  }
  else {
    param2 = (int *)param2[2];
  }
  if (*param3 == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = param3[2];
  }
  iVar6 = *(int *)(DAT_01223520 + 0x2c);
  if (*(int *)(iVar6 + 0x14) == 0) {
    return 0;
  }
  puVar4 = *(undefined4 **)(iVar6 + 8);
  if (puVar4 == (undefined4 *)0x0) {
    if (*(int **)(iVar6 + 0x1c) != (int *)0x0) {
      puVar4 = (undefined4 *)
               (**(code **)(**(int **)(iVar6 + 0x1c) + 4))
                         (*(undefined4 *)(iVar6 + 0xc),*(undefined4 *)(iVar6 + 0x10));
      goto LAB_005f777b;
    }
  }
  else {
    uVar5 = *(int *)(iVar6 + 0x14) - 1;
    *(undefined4 *)(iVar6 + 8) = *puVar4;
    *(uint *)(iVar6 + 0x14) = uVar5;
    if (uVar5 < *(uint *)(iVar6 + 0x18)) {
      *(uint *)(iVar6 + 0x18) = uVar5;
    }
LAB_005f777b:
    if (puVar4 != (undefined4 *)0x0) {
      iVar6 = FUN_005f6510(piVar3,param4);
      if ((iVar6 != 0) && (-1 < param5)) {
        *(int *)(iVar6 + 0x2c) = param5;
      }
      goto LAB_005f77a1;
    }
  }
  iVar6 = 0;
LAB_005f77a1:
  *(undefined4 *)(iVar6 + 0x44) = param6;
  *(undefined4 *)(iVar6 + 0x4c) = param7;
  *(undefined4 *)(iVar6 + 0x48) = param8;
  if (param2 == (int *)iVar7) {
    *(uint *)(iVar6 + 0x38) = *(uint *)(iVar6 + 0x38) | 9;
  }
  else {
    FUN_005f8520(iVar6,*(undefined4 *)(thisPtr + 0x24));
  }
  uVar2 = *(undefined4 *)(thisPtr + 0x4c);
  puVar4 = *(undefined4 **)(thisPtr + 0x38);
  if (puVar4 == (undefined4 *)0x0) {
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0;
    puVar4 = &uStack_c;
  }
  puVar4 = (undefined4 *)(**(code **)**(undefined4 **)(thisPtr + 0x34))(0xc,puVar4);
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = uVar2;
  }
  puVar1 = puVar4 + 1;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = uStack_4;
  }
  if (puVar4 + 2 != (int *)0x0) {
    puVar4[2] = iVar6;
  }
  FUN_005f9d10();
  *(undefined4 **)(unaff_EBX + 4) = puVar4;
  *(undefined4 **)*puVar1 = puVar4;
  return iVar6;
}