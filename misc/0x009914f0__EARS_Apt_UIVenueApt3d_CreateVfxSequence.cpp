// Xbox PDB: EARS_Apt_UIVenueApt3d_CreateVfxSequence
// FUNC_NAME: EventScheduler::processBuildingEvent
undefined4 __thiscall EventScheduler::processBuildingEvent(int this, undefined4 param_2, uint eventId)
{
  int node;
  uint oldNode;
  char charVar;
  int buildingPtr;
  int type;
  int *pRMinus;
  int *pRPlus;
  undefined4 result;
  undefined1 *nameStr;
  undefined4 *newEvent;
  int *piVar9;
  int local_1bc;
  int *local_1b8;
  int *local_1b4;
  float colorR;
  float colorG;
  float colorB;
  undefined4 local_1a4;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined1 local_190[48];
  undefined4 local_160;
  float local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined1 local_150[52];
  float local_11c;
  undefined1 local_110[268];

  node = *(int *)(this + 0x60);
  if (node == 0) {
    return 2;
  }
  while ((int)*(short *)(node + 0x44) != eventId) {
    if (eventId < (uint)(int)*(short *)(node + 0x44)) {
      return 2;
    }
    node = *(int *)(node + 4);
    if (node == 0) {
      return 2;
    }
  }
  local_1bc = this;
  buildingPtr = FUN_006b0ee0(*(undefined4 *)(node + 0x40));
  if (buildingPtr == 0) {
    return 2;
  }
  type = *(int *)(buildingPtr + 0xc4);
  local_1b8 = (int *)(node + 0x38);
  local_1b4 = (int *)(node + 0x3c);
  if (type == 1) {
    if ((*(byte *)(local_1bc + 0x88) & 1) == 0) {
      return 2;
    }
  }
  else if ((*(byte *)(local_1bc + 0x88) & 2) == 0) {
    return 2;
  }
  FUN_00425060(&local_19c, 0);
  FUN_0056b8a0(local_198, local_19c, local_194, local_190);
  local_160 = *(undefined4 *)(buildingPtr + 0x10);
  charVar = FUN_00976e60(buildingPtr, local_150);
  if (charVar == '\0') {
    local_11c = *(float *)(buildingPtr + 0x14);
  }
  local_15c = local_11c + _DAT_00d91d80;
  local_158 = *(undefined4 *)(buildingPtr + 0x18);
  local_154 = _DAT_00d5780c;
  if (type == 9) {
    node = FUN_008ff310(*(undefined4 *)(node + 0x40));
    if (node == 0) goto LAB_0099184f;
    result = FUN_0045c740(&local_1bc, "dv_hit_hangout", local_190, 0x2ff, 4, 0, 0xffffffff, 0);
    FUN_00414db0(result);
    FUN_00414df0();
    node = FUN_008fdfb0();
    if (node == 0) goto LAB_0099184f;
    node = FUN_00791540();
  }
  else {
    piVar9 = *(int **)(buildingPtr + 0xc0);
    if (piVar9 == (int *)0x0) {
      result = FUN_006af820(*(undefined4 *)(buildingPtr + 0xc4));
      FUN_005c4630(local_110, 0x100, "dv_%s", result);
    }
    else {
      node = FUN_0084a410();
      if (node == 0x637b907) {
        FUN_005c4630(local_110, 0x100, "%s_monopoly", *piVar9 + 0x38);
      }
      else {
        FUN_005c4660(local_110, *piVar9 + 0x38, 0x100, 0);
      }
    }
    result = FUN_0045c740(&local_1bc, local_110, local_190, 0x2ff, 4, 0, 0xffffffff, 0);
    FUN_00414db0(result);
    if (local_1bc != 0) {
      *(undefined4 *)(local_1bc + 8) = 0;
    }
    node = FUN_006b4860();
    if (node == 0) {
      if (*(int *)(buildingPtr + 0x174) != 0) {
        nameStr = *(undefined1 **)(buildingPtr + 0x15c);
        if (nameStr == (undefined1 *)0x0) {
          nameStr = &DAT_0120546e;
        }
        goto LAB_009917b5;
      }
    }
    else {
      nameStr = *(undefined1 **)(buildingPtr + 0x14c);
      if (nameStr == (undefined1 *)0x0) {
        nameStr = &DAT_0120546e;
      }
LAB_009917b5:
      result = FUN_0045c740(&local_1bc, nameStr, local_190, 0x2ff, 4, 0, 0xffffffff, 0);
      FUN_00414db0(result);
      FUN_00414df0();
    }
    node = FUN_008c74d0(*(undefined4 *)(buildingPtr + 0x40));
    piVar9 = local_1b8;
  }
  if (node != 0) {
    oldNode = *(uint *)(node + 0xf8);
    colorR = (float)(oldNode & 0xff);
    colorG = (float)(oldNode >> 8 & 0xff);
    colorB = (float)(oldNode >> 0x10 & 0xff);
    local_1a4 = 0;
    if (*piVar9 != 0) {
      FUN_004df760(&colorR);
    }
    if (*local_1b4 != 0) {
      FUN_004df760(&colorR);
    }
  }
LAB_0099184f:
  newEvent = (undefined4 *)FUN_004eb390(0xc, 0x10);
  if (newEvent == (undefined4 *)0x0) {
    newEvent = (undefined4 *)0x0;
  }
  else {
    newEvent[1] = 0;
    *newEvent = &PTR_LAB_00d91d84;
    newEvent[2] = 0;
  }
  newEvent[2] = eventId;
  FUN_004df830(newEvent);
  return 2;
}