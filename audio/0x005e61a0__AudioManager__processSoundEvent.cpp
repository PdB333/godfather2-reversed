// FUNC_NAME: AudioManager::processSoundEvent
undefined4 __thiscall AudioManager::processSoundEvent(int thisPtr, int **eventParams, int extraData)

{
  int soundIdx;
  ushort uVar2;
  bool bVar3;
  uint in_EAX;
  undefined4 uVar4;
  int iVar5;
  ushort uVar6;
  int *piVar7;
  float10 fVar8;
  float fVar9;
  float local_30;
  float local_2c;
  int *local_20;
  int local_1c;
  float local_18;
  undefined4 local_14;
  
  uVar4 = 0;
  // +0x603c probably sound slot array pointer
  if ((((*(int *)(thisPtr + 0x603c) != 0) && (eventParams[5] < (int *)0x200)) &&
      (piVar7 = (int *)((int)eventParams[5] * 0x74 + *(int *)(thisPtr + 0x603c)), piVar7 != (int *)0x0))
     && (soundIdx = *piVar7, soundIdx != 0)) {
    local_2c = 0.0;
    local_18 = DAT_00e2b1a4;  // some constant, maybe 1.0?
    if ((*(byte *)(soundIdx + 7) & 1) != 0) {
      iVar5 = 0;
      if (in_EAX != 0) {
        if (piVar7 + 0xf == (int *)0x0) {
          iVar5 = 0;
        }
        else {
          iVar5 = FUN_005e5900(piVar7 + 0xf);  // findParameterIndex
        }
        local_2c = (float)piVar7[iVar5 + 0xf];  // get parameter value
      }
      local_30 = local_2c;
      if ((in_EAX != 0) && (extraData = extraData + iVar5 * 0x30, (*(byte *)(extraData + 0x2c) & 1) != 0))
      {
        if (eventParams[7] == (int *)0x0) {
          FUN_00414c60(eventParams,extraData + 0x10,&local_20);  // allocateTemporaryBuffer?
          eventParams = &local_20;
        }
        fVar8 = (float10)FUN_004bcfb0(eventParams);  // calculateOcclusionFilter
        local_30 = (float)fVar8;
      }
      local_18 = local_30 - *(float *)(soundIdx + 8);  // difference from current pan/volume
      if (0.0 <= local_18) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
        fVar9 = local_18;
        if ((in_EAX < 2) && (piVar7 != (int *)0xfffffff4)) {
          FUN_005e5980(in_EAX);  // adjustSoundParameter
          fVar9 = local_2c;
        }
        local_18 = DAT_00e2b1a4;
        if ((*(byte *)(soundIdx + 7) & 2) == 0) {
          piVar7[0x15] = (int)DAT_00e2b1a4;  // set to default
        }
        else {
          FUN_005e5c60(piVar7 + 0xf,piVar7[0x14],*(undefined4 *)(soundIdx + 0x3c),piVar7 + 0x15);  // interpolateSound
          local_18 = fVar9;
        }
      }
      piVar7[0x14] = (int)local_30;  // store current value
      if ((bVar3) ||
         ((piVar7[2] != 0 && (local_18 = *(float *)(piVar7[2] + 0x50), DAT_00e44598 < local_18)))) {
        FUN_005e5b00(*(undefined4 *)(soundIdx + 0xc),*(undefined4 *)(soundIdx + 8),
                     *(undefined4 *)(soundIdx + 0x14));  // playSoundEvent
      }
      else {
        local_18 = 0.0;
      }
    }
    uVar4 = local_14;
    local_14 = CONCAT13((char)piVar7[0x16],(undefined3)local_14);
    uVar2 = (*(byte *)((int)piVar7 + 0x5a) & 3) * 2;
    uVar6 = uVar2 | (ushort)uVar4 & 0xff01;
    local_14 = CONCAT22(local_14._2_2_,uVar6);
    if ((char)uVar2 == '\x02') {
      local_14 = CONCAT22(local_14._2_2_,uVar6) & 0xfffffff9 | 0x80;
    }
    local_20 = piVar7;
    local_1c = soundIdx + 0x20;
    FUN_005f1f80(&local_20);  // updateSoundStateMachine
    uVar4 = 1;
  }
  return uVar4;
}