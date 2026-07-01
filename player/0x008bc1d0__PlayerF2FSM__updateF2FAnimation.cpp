// FUNC_NAME: PlayerF2FSM::updateF2FAnimation
void __fastcall PlayerF2FSM::updateF2FAnimation(int *this)
{
  float fVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong local_c;
  
  if ((*(byte *)((int)this + 0x2b2) & 1) != 0) {
    FUN_00894c90(0xdab8f267);
  }
  if (((((this[0xa4] != 0) || (this[0xa5] != 0)) || (this[0xa6] != 0)) ||
      (uVar4 = DAT_012054b4, this[0xa7] != 0)) &&
     (uVar4 = DAT_012054b4 + 1,
     *(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4) <= (float)this[0xa8])) {
    DAT_012054b4 = DAT_012054b4 + 2;
    iVar5 = this[0xaa] - this[0xa9];
    fVar1 = (float)iVar5;
    if (iVar5 < 0) {
      fVar1 = fVar1 + DAT_00e44578;
    }
    uVar8 = 0;
    uVar7 = 0;
    uVar6 = 0;
    local_c = (longlong)ROUND(fVar1 * *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar4) * 4));
    iVar5 = (int)local_c + this[0xa9];
    uVar2 = FUN_00445f00(this);
    piVar3 = (int *)FUN_00856780(this + 0xa4,uVar2,uVar6,uVar7,uVar8);
    uVar4 = DAT_012054b4;
    if (piVar3 != (int *)0x0) {
      piVar3[0xa5] = iVar5;
      FUN_008bc150(&local_c);
      iVar5 = *piVar3;
      if ((*(byte *)((int)this + 0x2b2) & 2) == 0) {
        uVar2 = (**(code **)(*this + 0x58))(0,0x3f800000,0);
      }
      else {
        uVar2 = (**(code **)(*this + 0x58))(1,DAT_00d5ddec,DAT_00d5ddec);
      }
      (**(code **)(iVar5 + 0x170))(&local_c,uVar2);
      *(undefined1 *)((int)this + 0x2b1) = 1;
      uVar4 = DAT_012054b4;
    }
  }
  DAT_012054b4 = uVar4;
  return;
}