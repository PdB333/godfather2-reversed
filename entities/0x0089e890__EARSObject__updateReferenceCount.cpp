// FUNC_NAME: EARSObject::updateReferenceCount
void __thiscall EARSObject::updateReferenceCount(int *this, int *other)
{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  float10 fVar7;
  uint uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  (**(code **)(*(int *)*other + 4))(&local_20);
  fVar7 = (float10)(**(code **)(*(int *)*other + 8))();
  uVar5 = 0;
  FUN_004262f0(0);
  uStack_34 = uStack_24;
  uStack_30 = local_20;
  uStack_2c = uStack_1c;
  fStack_28 = (float)fVar7;
  iVar4 = FUN_004bdae0(&uStack_34);
  if (iVar4 != 2) {
    bVar1 = false;
    bVar2 = false;
    uStack_38 = 0;
    piVar6 = (int *)0x0;
    do {
      if (bVar2) {
        return;
      }
      if (3 < uVar5) goto LAB_0089e962;
      if (*this == *other) {
        bVar2 = true;
      }
      else {
        if (*this == 0) {
          bVar1 = true;
          uVar3 = uStack_38;
        }
        else {
          uVar3 = this[2];
          if ((uint)this[2] <= uStack_38) goto LAB_0089e951;
        }
        uStack_38 = uVar3;
        piVar6 = this;
      }
LAB_0089e951:
      uVar5 = uVar5 + 1;
      this = this + 3;
    } while (!bVar1);
    if (!bVar2) {
LAB_0089e962:
      if (piVar6 != (int *)0x0) {
        if (piVar6 != other) {
          iVar4 = *other;
          if (*piVar6 != iVar4) {
            if (*piVar6 != 0) {
              FUN_004daf90(piVar6);
            }
            *piVar6 = iVar4;
            if (iVar4 != 0) {
              piVar6[1] = *(int *)(iVar4 + 4);
              *(int **)(iVar4 + 4) = piVar6;
            }
          }
        }
        piVar6[2] = 0;
      }
    }
  }
  return;
}