// FUNC_NAME: PlayerF2FSM::updateState
void __thiscall PlayerF2FSM::updateState(int this, float deltaTime)
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  bool bVar5;
  float fVar6;
  
  // Decrement timer at +0x14
  if (0.0 < *(float *)(this + 0x14)) {
    *(float *)(this + 0x14) = *(float *)(this + 0x14) - deltaTime;
  }
  // If timer still positive, skip state update
  if (0.0 < *(float *)(this + 0x14)) {
    return;
  }
  
  iVar3 = *(int *)(this + 4); // current state
  iVar1 = *(int *)(*(int *)(this + 0xc) + 0x54); // some object ID or type
  
  switch(iVar3) {
  case 1: // State 1 - e.g., Idle
    if ((((iVar1 == 0x637b907) && ((*(byte *)(*(int *)(this + 8) + 0x5f) & 1) != 0)) &&
        (cVar2 = FUN_00791230(), cVar2 != '\0')) &&
       ((*(uint *)(*(int *)(this + 8) + 0x5c) >> 0x14 & 1) == 0)) {
      FUN_00791250(*(undefined4 *)(this + 0xc),0xffffffff);
    }
    break;
  case 3: // State 3 - e.g., Moving
    if (iVar1 == 0x637b907) goto switchD_008c8dfb_caseD_6;
    cVar2 = FUN_00791230();
    if (cVar2 == '\0') {
      return;
    }
    if ((*(uint *)(*(int *)(this + 8) + 0x5c) >> 0x14 & 1) != 0) {
      return;
    }
    iVar3 = FUN_008c8180();
    if (*(int *)(this + 0x18) == iVar3) {
      iVar3 = *(int *)(this + 4);
      if (iVar3 == 1) {
        return;
      }
      *(undefined4 *)(this + 0x14) = 0;
      goto LAB_008c8e91;
    }
    FUN_008c8a80(1);
    iVar3 = *(int *)(this + 4);
    fVar6 = *(float *)(*(int *)(this + 0xc) + 0x1e4);
    if (iVar3 == 3) goto LAB_008c8ee4;
    bVar5 = fVar6 < _DAT_00d577a0;
    goto LAB_008c8ec5;
  case 4: // State 4 - e.g., Exiting
    FUN_008c8d00(*(undefined4 *)(this + 0x18));
    return;
  case 5: // State 5 - e.g., Entering
    if (iVar1 == 0x637b907) {
      FUN_008c8cb0();
      return;
    }
    fVar6 = *(float *)(*(int *)(this + 0xc) + 0x1e4);
    if (iVar3 == 3) goto LAB_008c8ee4;
    bVar5 = fVar6 < 0.0;
LAB_008c8ec5:
    if (!bVar5) {
      *(float *)(this + 0x14) = fVar6;
    }
    FUN_008c83b0(iVar3,3,*(undefined4 *)(this + 0x14));
    *(undefined4 *)(this + 4) = 3;
LAB_008c8ee4:
    uVar4 = FUN_008c8180();
    FUN_008c80d0(uVar4);
    return;
  case 6: // State 6 - e.g., Special
switchD_008c8dfb_caseD_6:
    if (iVar3 != 1) {
      *(undefined4 *)(this + 0x14) = 0;
LAB_008c8e91:
      FUN_008c83b0(iVar3,1,0);
      *(undefined4 *)(this + 4) = 1;
      return;
    }
  }
  return;
}