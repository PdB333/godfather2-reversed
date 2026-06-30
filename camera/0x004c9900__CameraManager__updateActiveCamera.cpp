// FUNC_NAME: CameraManager::updateActiveCamera
void CameraManager::updateActiveCamera(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  float fVar5;
  undefined4 local_18;
  undefined4 local_14;
  
  fVar5 = 0.0;
  iVar1 = *(int *)(param_1 + 0x10); // +0x10: camera list
  iVar2 = **(int **)(iVar1 + 0x1c); // +0x1c: iterator
  local_18 = 0;
  local_14 = 0.0;
  while( true ) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x10) + 0x1c);
    if ((iVar1 == 0) || (iVar1 != *(int *)(param_1 + 0x10))) {
      FUN_00b97aea(); // assert or error handler
    }
    if (iVar2 == iVar3) break;
    if (iVar1 == 0) {
      FUN_00b97aea();
    }
    if (iVar2 == *(int *)(iVar1 + 0x1c)) {
      FUN_00b97aea();
    }
    iVar3 = *(int *)(iVar2 + 0x10); // +0x10: camera priority/weight
    FUN_004c90f0(); // evaluateCamera
    if (local_14 < fVar5) {
      local_18 = iVar3;
      local_14 = fVar5;
    }
    FUN_004cab50(); // nextCamera
  }
  iVar1 = *(int *)(param_1 + 0x18); // +0x18: current active camera
  if (local_18 != iVar1) {
    if (iVar1 != 0) {
      FUN_0043e500(iVar1); // deactivateCamera
      iVar1 = *(int *)(param_1 + 0x18);
      if ((*(char *)(iVar1 + 4) != '\0') && (*(int *)(iVar1 + 0x290) != 0)) {
        FUN_005ddd90(DAT_01223508,*(int *)(iVar1 + 0x290)); // stopAudio
        *(undefined1 *)(iVar1 + 4) = 0;
      }
    }
    if (local_18 != 0) {
      FUN_0043e500(local_18); // activateCamera
      if (*(int *)(local_18 + 0x290) != 0) {
        cVar4 = FUN_005ddc30(DAT_01223508); // canPlayAudio
        if (cVar4 != '\0') {
          *(undefined1 *)(local_18 + 4) = 1;
        }
      }
    }
    *(int *)(param_1 + 0x18) = local_18;
  }
  return;
}