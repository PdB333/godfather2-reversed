// FUNC_NAME: PlayerF2FSM::handleF2FInteraction
uint __thiscall PlayerF2FSM::handleF2FInteraction(int thisPtr, int targetEntityId)
{
  int iVar1;
  uint in_EAX;
  int *piVar2;
  int iVar3;
  int *result;
  undefined4 local_30 [2];
  float afStack_28 [2];
  undefined4 local_20 [7];
  
  iVar3 = 0;
  result = (int *)0x0;
  piVar2 = (int *)(thisPtr + 0x82b0); // +0x82b0: faceToFaceSlots array start (10 slots, 0x5c each)
  while ((*piVar2 < 0 || (*piVar2 != targetEntityId))) {
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 0x5c; // +0x5c: stride per F2F slot
    if (9 < iVar3) {
      return in_EAX & 0xffffff00;
    }
  }
  if (iVar3 < 0) {
    return in_EAX & 0xffffff00;
  }
  iVar1 = iVar3 * 0x170 + 0x8210 + thisPtr; // +0x8210: faceToFaceData array start (10 slots, 0x170 each)
  iVar3 = *(int *)(iVar3 * 0x170 + 0x82ac + thisPtr) * 0x10; // +0x82ac: slot index * 0x10
  piVar2 = (int *)(iVar3 + 0x81bc + thisPtr); // +0x81bc: some per-slot data pointer
  if (*(int *)(iVar3 + 0x81c4 + thisPtr) != 0) { // +0x81c4: check if slot is active
    iVar3 = FUN_005e9d10(); // getCurrentPlayer
    FUN_00c9cbe0(*(undefined4 *)(thisPtr + 0x580),*(undefined4 *)(iVar3 + 0x10),2,local_30); // getPlayerPosition
    FUN_00c9cbe0(*(undefined4 *)(thisPtr + 0x580),*(undefined4 *)(iVar3 + 0x10),3,local_20); // getPlayerFacing
    FUN_00ab4db0(&DAT_00e2aea0); // lockMutex
    local_30[0] = *(undefined4 *)(iVar1 + 0x134); // +0x134: distance to target
    local_20[0] = local_30[0];
    if (*(int *)(iVar1 + 0xa4) == 0) { // +0xa4: check if not already interacting
      if (DAT_00e2b05c <= *(float *)(iVar1 + 0x134)) { // compare distance threshold
        FUN_00c9eac0(); // beginInteraction
        FUN_00c9cd40(2,local_30); // setInteractionPosition
        FUN_00c9cd40(3,afStack_28); // setInteractionFacing
        FUN_00c9eae0(); // endInteraction
        if (afStack_28[0] == DAT_00e2b05c) {
          result = (int *)0x2; // success - interaction started
        }
        else {
          result = (int *)0x3; // failure - interaction cancelled
          LOCK();
          *piVar2 = *piVar2 + -1; // decrement slot count
          UNLOCK();
          FUN_005ea0d0(); // cleanupInteraction
        }
      }
    }
    else {
      result = (int *)0x1; // already interacting
    }
    FUN_00ab4e70(); // unlockMutex
    if ((result == (int *)0x2) || (piVar2 = result, result == (int *)0x1)) {
      return 1; // success
    }
  }
  return (uint)piVar2 & 0xffffff00; // failure
}