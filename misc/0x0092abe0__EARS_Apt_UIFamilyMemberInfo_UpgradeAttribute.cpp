// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_UpgradeAttribute
// FUNC_NAME: PlayerReputationTracker::updateCurrentAttribute
void __fastcall PlayerReputationTracker::updateCurrentAttribute(int this)
{
  int *piVar1;
  int iVar2;
  float fVar3;
  undefined4 uVar4;
  
  piVar1 = (int *)FUN_009b9490(*(int *)(this + 0x50) == 0);
  iVar2 = *(int *)(*(int *)(this + 0x118) + *(int *)(this + 0xf4) * 4) +
          *(int *)(this + 0xf8);
  if (*(int *)(this + 0x124) != 0) {
    if (*(int *)(this + 0xf8) != 0) {
      (**(code **)(**(int **)(this + 0x124) + 0x24))(*(undefined4 *)(*piVar1 + -4 + iVar2 * 4));
    }
    (**(code **)(**(int **)(this + 0x124) + 0x20))(*(undefined4 *)(*piVar1 + iVar2 * 4));
    uVar4 = 9;
    fVar3 = (float)FUN_009b9ae0(9);
    FUN_0092a900((float)fVar3, uVar4);
    if (*(int *)(this + 0x50) == 0) {
      FUN_00894c90(0x5b859ffc);
    }
  }
  FUN_005a04a0("UpdateCurrentAttribute", 0, &DAT_00d88708, 0);
  return;
}