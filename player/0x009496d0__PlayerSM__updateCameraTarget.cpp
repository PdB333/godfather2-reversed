// FUNC_NAME: PlayerSM::updateCameraTarget
void __thiscall PlayerSM::updateCameraTarget(int this, int cameraTarget)
{
  int *currentTargetPtr;
  int iVar2;
  undefined4 uVar3;
  
  currentTargetPtr = (int *)(this + 0x154);
  if (*(int *)(this + 0x118) == 1) {
    if (cameraTarget == 0) {
      cameraTarget = 0;
    }
    else {
      cameraTarget = cameraTarget + 0x48;
    }
    if (*currentTargetPtr != cameraTarget) {
      if (*currentTargetPtr != 0) {
        FUN_004daf90(currentTargetPtr); // likely linked list removal
      }
      *currentTargetPtr = cameraTarget;
      if (cameraTarget != 0) {
        *(undefined4 *)(this + 0x158) = *(undefined4 *)(cameraTarget + 4);
        *(int **)(cameraTarget + 4) = currentTargetPtr;
      }
    }
  }
  else if (*currentTargetPtr != 0) {
    FUN_004daf90(currentTargetPtr); // likely linked list removal
    *currentTargetPtr = 0;
  }
  if ((*currentTargetPtr == 0) || (*currentTargetPtr == 0x48)) {
    uVar3 = 0;
    *(undefined4 *)(this + 0x138) = 0;
    *(undefined4 *)(this + 0x134) = 0;
    *(undefined4 *)(this + 0x130) = 0;
  }
  else {
    iVar2 = FUN_00471610(); // likely getPlayerCamera()
    uVar3 = _DAT_00d5780c; // global camera data
    *(undefined4 *)(this + 0x130) = *(undefined4 *)(iVar2 + 0x30);
    *(undefined4 *)(this + 0x134) = *(undefined4 *)(iVar2 + 0x34);
    *(undefined4 *)(this + 0x138) = *(undefined4 *)(iVar2 + 0x38);
  }
  *(undefined4 *)(this + 0x13c) = uVar3;
  if (*currentTargetPtr != 0) {
    uVar3 = FUN_00949080(*currentTargetPtr + -0x48); // likely getCameraFromTarget
    *(undefined4 *)(this + 0x164) = uVar3;
    return;
  }
  uVar3 = FUN_00949080(0); // likely getCameraFromTarget with null
  *(undefined4 *)(this + 0x164) = uVar3;
  return;
}