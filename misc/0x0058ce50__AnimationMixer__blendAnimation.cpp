// FUNC_NAME: AnimationMixer::blendAnimation
undefined4 __thiscall AnimationMixer::blendAnimation(float param_1,undefined4 param_2,float param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  code *pcVar4;
  int iVar5;
  undefined4 uVar6;
  float fVar7;
  float local_4;
  
  piVar2 = *(int **)((int)param_3 + 4);
  if (*(char *)((int)param_3 + 1) < '\x01') {
    return 0;
  }
  pbVar3 = *(byte **)((int)param_3 + 0xc);
  iVar5 = *piVar2;
  local_4 = param_1;
  if (((-1 < iVar5) && (iVar5 < DAT_01205574)) &&
     (pcVar4 = *(code **)(DAT_01205570 + 4 + iVar5 * 0xc), pcVar4 != (code *)0x0)) {
    (*pcVar4)(param_2,iVar5,&local_4);
  }
  param_3 = (local_4 - (float)piVar2[1]) / (float)piVar2[2];
  fVar7 = 0.0;
  if ((param_3 <= 0.0) || (fVar7 = DAT_00e2b1a4, DAT_00e2b1a4 < param_3)) {
    param_3 = fVar7;
  }
  bVar1 = *pbVar3;
  if ((bVar1 & 0x3f) < 0x23) {
    iVar5 = (**(code **)(&DAT_0103afc0 + (bVar1 & 0x3f) * 4))
                      (param_2,pbVar3,param_4,param_5,param_6,param_7,param_8);
    if (iVar5 == 0) {
      FUN_0056fb60();
      return 0;
    }
    uVar6 = FUN_005850c0(iVar5,param_3,param_7);
    FUN_0056fb60();
    return uVar6;
  }
  FUN_0056fb60();
  return 0;
}