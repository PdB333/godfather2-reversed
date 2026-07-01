// FUNC_NAME: PlayerSM::updateGroundState

undefined4 __thiscall PlayerSM::updateGroundState(int thisPtr, int param2)
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  undefined4 uVar7;
  float10 fVar8;
  float local_4;
  
  iVar6 = *(int *)(*(int *)(thisPtr + 0x58) + 0x74c); // +0x58 -> PlayerSM member, +0x74c -> unknown offset
  if (iVar6 == 0) {
    iVar6 = 0;
  }
  else {
    iVar6 = iVar6 + -0x48;
  }
  cVar5 = FUN_007ab250(); // likely isPaused or similar
  if ((cVar5 == '\0') || (cVar5 = FUN_004ac2c0(0), cVar5 != '\0')) { // check if game is not paused OR some input state
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (*(char *)(iVar6 + 0x1a8) != '\x01') { // +0x1a8: likely a ground state flag
    return 1;
  }
  fVar8 = (float10)FUN_00701020(); // get delta time
  local_4 = (float)fVar8;
  cVar5 = FUN_00701280(); // likely isPlayerOnGround
  if (cVar5 != '\0') {
    uVar1 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x8e0); // +0x8e0: flags bitfield
    if ((((uVar1 >> 0x19 & 1) == 0) ||
        (uVar2 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x8e4), (uVar2 >> 6 & 1) != 0)) ||
       ((uVar2 >> 9 & 1) != 0)) {
      if (((uVar1 >> 1 & 1) == 0) || (cVar5 = FUN_00701010(), cVar5 != '\0')) { // likely isInputHeld
        cVar5 = FUN_00701010();
        if (cVar5 == '\0') {
          local_4 = local_4 + _DAT_00d6f878; // gravity modifier 1
        }
      }
      else {
        local_4 = local_4 + _DAT_00d6f874; // gravity modifier 2
      }
    }
    else {
      local_4 = local_4 + _DAT_00d6f874;
    }
  }
  if (bVar3) {
    iVar6 = FUN_007ab290(); // likely getFrameTime
    fVar4 = (float)(param2 - iVar6);
    if (param2 - iVar6 < 0) {
      fVar4 = fVar4 + DAT_00e44578; // some wrap-around constant
    }
    if (local_4 * DAT_00d60d04 <= fVar4) {
      cVar5 = FUN_00701010();
      if (cVar5 == '\0') {
        return 1;
      }
      uVar7 = FUN_00798f50(0x38); // likely allocate memory
      cVar5 = FUN_0079e920(uVar7); // likely object constructor
      if (cVar5 != '\0') {
        cVar5 = FUN_00701280();
        if (cVar5 != '\0') {
          return 0;
        }
        return 1;
      }
      return 1;
    }
  }
  cVar5 = FUN_007ab250();
  if ((cVar5 != '\0') && (_DAT_00d6f86c < *(float *)(thisPtr + 0x30))) { // +0x30: some timer
    return 1;
  }
  return 0;
}