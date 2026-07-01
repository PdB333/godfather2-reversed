// FUNC_NAME: Vehicle::checkCollisionAndSteering
undefined4 __thiscall Vehicle::checkCollisionAndSteering(int *this, undefined4 param_2)

{
  char cVar1;
  int iVar2;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar3;
  double dVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined8 uStack_30;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float local_18;
  float fStack_14;
  float local_10;
  float afStack_c [3];
  
  // +0x452: some speed/velocity related field
  local_40 = (float)this[0x452];
  local_48 = 0.0;
  // +0x414, +0x415, +0x416: position components (x, y, z)
  local_3c = (float)this[0x414];
  local_38 = (float)this[0x415];
  local_34 = (float)this[0x416];
  // +1000: some timer/accumulator, +0x3e9: another timer, DAT_00d5eee4: global multiplier
  local_44 = ((float)this[1000] + (float)this[0x3e9]) * DAT_00d5eee4;
  FUN_008750c0(&local_18);
  uVar10 = 1;
  pfVar7 = &local_40;
  uVar9 = 0;
  uVar8 = 0;
  pfVar6 = &local_48;
  pfVar5 = &local_3c;
  dVar4 = (double)local_18;
  fVar3 = local_40;
  FUN_00b9a9fa(pfVar5,local_40,pfVar6,0,0,pfVar7,1);
  cVar1 = FUN_00862970(param_2,(float)dVar4,pfVar5,fVar3,pfVar6,uVar8,uVar9,pfVar7,uVar10);
  if (cVar1 != '\\0') {
    (**(code **)(*this + 0x1b0))(); // vtable call at +0x1b0 (likely getSpeed or similar)
    fVar3 = DAT_00d68260;
    if ((float10)DAT_00d68260 < extraout_ST0) {
      (**(code **)(*this + 0x1b0))();
      fVar3 = (float)extraout_ST0_00;
    }
    if (local_40 < fVar3 * local_44 * DAT_00d5ef70) {
      return 0;
    }
  }
  iVar2 = FUN_00471610(); // likely getCameraManager or getPlayerCamera
  uStack_30 = *(undefined8 *)(iVar2 + 0x30);
  fStack_28 = *(float *)(iVar2 + 0x38);
  FUN_008750c0(&fStack_24);
  fVar3 = (float)this[1000] + (float)this[0x3e6] + (float)this[0x3e9];
  uStack_30 = CONCAT44(fStack_20 * fVar3 + uStack_30._4_4_,fStack_24 * fVar3 + (float)uStack_30);
  fStack_28 = fStack_1c * fVar3 + fStack_28;
  FUN_00601970(this[0x452],&local_18);
  iVar2 = this[0x452];
  fVar3 = (float)this[1000] + (float)this[0x3e6] + (float)this[0x3e9];
  local_3c = local_18 * fVar3 + local_3c;
  local_38 = fStack_14 * fVar3 + local_38;
  local_34 = local_10 * fVar3 + local_34;
  FUN_008750c0(afStack_c);
  uVar11 = 0;
  uVar10 = 0;
  uVar9 = 0;
  uVar8 = 0;
  pfVar7 = &local_48;
  pfVar6 = &local_3c;
  dVar4 = (double)afStack_c[0];
  FUN_00b9a9fa(pfVar6,iVar2,pfVar7,0,0,0,0);
  cVar1 = FUN_00862970(&uStack_30,(float)dVar4,pfVar6,iVar2,pfVar7,uVar8,uVar9,uVar10,uVar11);
  if ((cVar1 != '\\0') && (local_48 < local_44)) {
    return 0;
  }
  return 1;
}