// FUNC_NAME: Entity::processCollisionOrTrigger
undefined4 * Entity::processCollisionOrTrigger(int this, int otherEntity, undefined4 param3, int param4, undefined4 param5)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  
  if (otherEntity == param4) {
    if ((*(int *)(otherEntity + 0x40) != 0) && ((*(byte *)(this + 0x20) & 2) == 0)) {
      iVar3 = FUN_005f8190(this, otherEntity, param3); // checkCollisionType?
      bVar1 = false;
      if ((iVar3 != 2) &&
         (((*(byte *)(this + 0x20) & 0xc) == 0 &&
          (uVar7 = 0, bVar2 = false, *(short *)(otherEntity + 0x3c) != 0)))) {
        do {
          bVar1 = bVar2;
          if (bVar1) break;
          iVar4 = FUN_005fcd80(uVar7); // checkSomeCondition?
          if (iVar4 != 0) {
            bVar1 = true;
          }
          uVar7 = uVar7 + 1;
          bVar2 = bVar1;
        } while (uVar7 < *(ushort *)(otherEntity + 0x3c));
      }
      if (iVar3 == 1) {
        if (bVar1) {
          *(int *)(this + 0x3c) = this; // self-reference?
        }
        else {
          iVar3 = FUN_005f8300(param3); // getSomeData?
          if (iVar3 != 0) {
            FUN_005f8260(*(int *)(this + 0x24) + (uint)*(byte *)(iVar3 + 0xb) * 0xc, iVar3, param5); // processData?
            uVar5 = FUN_005f6430(); // getTimestamp?
            *(uint *)(this + 0x38) = *(uint *)(this + 0x38) | 1;
            *(undefined4 *)(this + 0x34) = uVar5;
          }
        }
      }
      else {
        if (iVar3 == 0) goto LAB_005f84a0;
        if ((iVar3 == 2) && ((*(byte *)(this + 0x20) & 8) != 0)) goto LAB_005f84a2;
      }
    }
  }
  else {
    if ((*(byte *)(this + 0x20) & 0xc) == 0) {
      uVar7 = 0;
      bVar1 = false;
      if (*(short *)(otherEntity + 0x3c) != 0) {
        do {
          if (bVar1) goto LAB_005f84a6;
          iVar3 = FUN_005fcd80(uVar7);
          if (iVar3 != 0) {
            bVar1 = true;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < *(ushort *)(otherEntity + 0x3c));
LAB_005f84a0:
        if (bVar1) goto LAB_005f84a6;
      }
    }
LAB_005f84a2:
    *(uint *)(this + 0x38) = *(uint *)(this + 0x38) | 2;
  }
LAB_005f84a6:
  iVar4 = DAT_01223520; // global singleton?
  iVar3 = *(int *)(DAT_01223520 + 0x30);
  if (*(int *)(iVar3 + 0x14) != 0) {
    puVar6 = *(undefined4 **)(iVar3 + 8);
    if (puVar6 == (undefined4 *)0x0) {
      if (*(int **)(iVar3 + 0x1c) == (int *)0x0) goto LAB_005f850d;
      puVar6 = (undefined4 *)
               (**(code **)(**(int **)(iVar3 + 0x1c) + 4))
                         (*(undefined4 *)(iVar3 + 0xc), *(undefined4 *)(iVar3 + 0x10));
    }
    else {
      uVar5 = *puVar6;
      *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + -1;
      *(undefined4 *)(iVar3 + 8) = uVar5;
      if (*(uint *)(iVar3 + 0x14) < *(uint *)(iVar3 + 0x18)) {
        *(uint *)(iVar3 + 0x18) = *(uint *)(iVar3 + 0x14);
      }
    }
    if (puVar6 != (undefined4 *)0x0) {
      uVar5 = *(undefined4 *)(iVar4 + 0x1c);
      puVar6[2] = puVar6 + 3;
      puVar6[1] = uVar5;
      *puVar6 = 0;
      *(undefined4 **)(this + 0x30) = puVar6;
      return puVar6;
    }
  }
LAB_005f850d:
  *(uint *)(this + 0x38) = *(uint *)(this + 0x38) | 0x44;
  return (undefined4 *)0x0;
}