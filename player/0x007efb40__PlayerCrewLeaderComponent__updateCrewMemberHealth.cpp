// FUNC_NAME: PlayerCrewLeaderComponent::updateCrewMemberHealth
void __thiscall PlayerCrewLeaderComponent::updateCrewMemberHealth(int this, undefined4 param_2)
{
  float fVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar2 = DAT_01205228;
  fVar3 = (float10)FUN_007f31c0(DAT_01205228);  // getCrewMemberHealth
  fVar1 = (float)fVar3;
  if (((float10)_DAT_00d70090 < fVar3) && ((double)fVar1 < DAT_00d70088)) {
    FUN_007f33f0(*(undefined4 *)(this + 0x8c));  // triggerLowHealthVFX
  }
  if ((_DAT_00d70080 < (double)fVar1) && (fVar1 < _DAT_00d5c458)) {
    FUN_007f33f0(*(undefined4 *)(this + 0xc4));  // triggerMediumHealthVFX
  }
  fVar3 = (float10)FUN_007f3200(uVar2);  // getCrewMemberHealthPercent
  if ((*(char *)(this + 0x5e2) != '\0') || (*(char *)(this + 0x5e0) != '\0')) {
    FUN_0056d370(0,DAT_00e44564 - (float)(fVar3 * (float10)DAT_00d5ef90),0,param_2);  // updateHealthBar
  }
  return;
}