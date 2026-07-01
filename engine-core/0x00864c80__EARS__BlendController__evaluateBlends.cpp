// FUNC_NAME: EARS::BlendController::evaluateBlends
undefined1 __thiscall EARS::BlendController::evaluateBlends(int this, float *outValueA, float *outValueB)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  undefined1 local_9;
  
  pfVar4 = param_3;
  fVar3 = DAT_00e44794;
  iVar1 = *(int *)(param_1 + 0x10d8); // +0x10d8: blendTrackA
  local_9 = 0;
  if (iVar1 == 0) {
    iVar8 = 0;
  }
  else {
    iVar8 = *(int *)(param_1 + 0x10e0); // +0x10e0: clipInstanceA
  }
  iVar2 = *(int *)(param_1 + 0x10e4); // +0x10e4: blendTrackB
  if (iVar2 == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = *(int *)(param_1 + 0x10ec); // +0x10ec: clipInstanceB
  }
  *param_3 = DAT_00e44794; // default blend weight
  *param_2 = fVar3;
  if (iVar8 != 0) {
    uVar6 = FUN_0085f630(iVar1); // getTrackStatus
    if ((uVar6 & 2) != 0) {
      cVar5 = FUN_0085f680(iVar1,iVar8,&param_3); // evaluateTrack
      if (cVar5 != '\\0') {
        FUN_00470250(iVar8); // releaseClip
        *pfVar4 = (float)extraout_ST0;
        local_9 = 1;
      }
    }
  }
  if (iVar7 != 0) {
    uVar6 = FUN_0085f630(iVar2); // getTrackStatus
    if ((uVar6 & 2) != 0) {
      cVar5 = FUN_0085f680(iVar2,iVar7,&param_3); // evaluateTrack
      if (cVar5 != '\\0') {
        FUN_00470250(iVar7); // releaseClip
        *param_2 = (float)extraout_ST0_00;
        return 1;
      }
    }
  }
  return local_9;
}