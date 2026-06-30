// FUNC_NAME: AnimationPlayer::processAnimationEvents
undefined4 __thiscall AnimationPlayer::processAnimationEvents(int thisPtr, char *eventData, int *eventArray, float startTime, float endTime, uint flags, undefined4 param_7)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  float fVar8;
  char *local_18;
  float local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_14 = (float)(int)eventData[1];
  if (local_14 == 0.0) {
    return 0;
  }
  pbVar5 = (byte *)0x0;
  local_c = (int)local_14;
  // Check if animation is playing (bit 0 of flags at +0x10 in some object)
  if (((*(byte *)(*(int *)(thisPtr + 0x7c) + 0x10) & 1) != 0) && (0 < (int)local_14)) {
    local_18 = eventData + 0xc;
    do {
      pbVar5 = *(byte **)local_18;
      if (*pbVar5 == 9) { // Event type 9 = keyframe event
        iVar7 = *(int *)(pbVar5 + 4);
        uVar2 = *(uint *)(iVar7 + 4);
        if ((uint)eventArray[1] <= uVar2) {
          local_10 = 0;
          FUN_00591c00(&local_10); // likely array resize
        }
        if (*(float *)(*eventArray + uVar2 * 4) == DAT_00e2b1a4) { // sentinel value
          uVar2 = *(uint *)(iVar7 + 4);
          if ((uint)eventArray[1] <= uVar2) {
            local_8 = 0;
            FUN_00591c00(&local_8);
          }
          *(float *)(*eventArray + uVar2 * 4) = DAT_00e2b04c; // reset to default
        }
      }
      local_18 = local_18 + 4;
      local_14 = (float)((int)local_14 + -1);
    } while (local_14 != 0.0);
  }
  local_14 = 0.0;
  local_10 = 0;
  fVar8 = 0.0;
  if (0 < local_c) {
    local_18 = eventData + 0xc;
    do {
      pbVar5 = *(byte **)local_18;
      if (*pbVar5 == 9) {
        iVar7 = *(int *)(pbVar5 + 4);
        uVar2 = *(uint *)(iVar7 + 4);
        if ((uint)eventArray[1] <= uVar2) {
          local_8 = 0;
          FUN_00591c00(&local_8);
        }
        fVar8 = local_14;
        if (*(float *)(*eventArray + uVar2 * 4) != DAT_00e2b04c) {
          uVar2 = *(uint *)(iVar7 + 4);
          if ((uint)eventArray[1] <= uVar2) {
            local_4 = 0;
            FUN_00591c00(&local_4);
          }
          *(float *)(*eventArray + uVar2 * 4) = DAT_00e2b1a4;
          goto LAB_0058b160;
        }
      }
      else {
LAB_0058b160:
        uVar6 = (uint)*(short *)(pbVar5 + 2);
        uVar2 = eventArray[1];
        if ((uVar2 <= uVar6) && (iVar7 = (uVar6 - uVar2) + 1, iVar7 != 0)) {
          FUN_005822d0(uVar2 + iVar7); // resize event array
          iVar3 = eventArray[1];
          iVar7 = iVar7 + iVar3;
          do {
            puVar1 = (undefined4 *)(*eventArray + iVar3 * 4);
            eventArray[1] = iVar3 + 1;
            if (puVar1 != (undefined4 *)0x0) {
              *puVar1 = 0;
            }
            iVar3 = eventArray[1];
          } while (iVar7 != iVar3);
        }
        fVar8 = *(float *)(*eventArray + uVar6 * 4) + local_14;
        if (startTime < fVar8) {
          if (0x22 < (*pbVar5 & 0x3f)) goto LAB_0058b28c;
          uVar4 = (**(code **)(&DAT_0103afc0 + (*pbVar5 & 0x3f) * 4))
                            (thisPtr,pbVar5,eventArray,startTime - local_14,endTime - local_14,flags,
                             param_7);
          goto LAB_0058b28e;
        }
      }
      local_14 = fVar8;
      local_18 = local_18 + 4;
      local_10 = local_10 + 1;
      fVar8 = local_14;
    } while (local_10 < local_c);
  }
  if ((*pbVar5 & 0x3f) < 0x23) {
    uVar4 = (**(code **)(&DAT_0103afc0 + (*pbVar5 & 0x3f) * 4))
                      (thisPtr,pbVar5,eventArray,startTime - fVar8,endTime - fVar8,flags,param_7);
  }
  else {
LAB_0058b28c:
    uVar4 = 0;
  }
LAB_0058b28e:
  // Handle special case for event type 2 (animation complete?)
  if ((((*eventData == '\x02') && (*(int *)(eventData + 4) != 0)) &&
      (*(int *)(*(int *)(eventData + 4) + 4) != 0)) && ((flags & 4) == 0)) {
    uVar4 = FUN_00583730(thisPtr,flags);
    FUN_0056fb60();
    return uVar4;
  }
  return uVar4;
}