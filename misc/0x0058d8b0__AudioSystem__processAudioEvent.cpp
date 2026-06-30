// FUNC_NAME: AudioSystem::processAudioEvent
undefined4 AudioSystem::processAudioEvent(int this, float param_2, int *param_3, undefined4 param_4, undefined4 param_5, uint param_6, undefined4 param_7)

{
  short sVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  float fVar8;
  
  piVar6 = param_3;
  iVar5 = (int)param_2;
  if (*(char *)((int)param_2 + 1) < '\x01') {
    return 0;
  }
  pbVar2 = *(byte **)((int)param_2 + 0xc);
  iVar3 = *(int *)((int)param_2 + 4);
  sVar1 = *(short *)(pbVar2 + 2);
  if ((uint)param_3[1] <= (uint)(int)sVar1) {
    param_2 = 0.0;
    FUN_00591c00(&param_2);
  }
  uVar4 = *(uint *)(iVar3 + 0xc);
  fVar8 = *(float *)(*piVar6 + sVar1 * 4) - DAT_00e2b1a4;
  if ((uint)piVar6[1] <= uVar4) {
    param_2 = 0.0;
    FUN_00591c00(&param_2);
  }
  iVar3 = *piVar6;
  param_2 = *(float *)(iVar3 + uVar4 * 4) * fVar8;
  FUN_00591730(param_1,iVar5,piVar6);
  fVar8 = *(float *)(iVar3 + uVar4 * 4) * fVar8;
  if (fVar8 < param_2) {
    param_6 = param_6 ^ 2;
  }
  if ((*pbVar2 & 0x3f) < 0x23) {
    uVar7 = (**(code **)(&DAT_0103afc0 + (*pbVar2 & 0x3f) * 4))
                      (param_1,pbVar2,piVar6,fVar8,param_2,param_6,param_7);
  }
  else {
    uVar7 = 0;
  }
  if (*(int *)(param_1 + 0x7c) != 0) {
    *(float *)(*(int *)(param_1 + 0x7c) + 0x20) = param_2;
    *(float *)(*(int *)(param_1 + 0x7c) + 0x1c) = fVar8;
  }
  return uVar7;
}