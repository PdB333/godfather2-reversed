// FUNC_NAME: Player::updateCameraTarget
void __thiscall Player::updateCameraTarget(int *thisPtr, int cameraTargetParam)
{
  int local_24;
  undefined4 local_20;
  int local_1c[3];
  code *local_10;
  
  if (cameraTargetParam == 0) {
    local_24 = 0;
  }
  else {
    // Offset +0x48: camera target data structure pointer
    local_24 = cameraTargetParam + 0x48;
  }
  local_20 = 0;
  if (local_24 != 0) {
    // Offset +0x04: pointer to next in linked list of camera targets
    local_20 = *(undefined4 *)(local_24 + 4);
    *(int **)(local_24 + 4) = &local_24;
  }
  FUN_008acfe0(&local_24);
  if (local_24 != 0) {
    FUN_004daf90(&local_24); // likely some cleanup/release
  }
  FUN_008a8ab0(cameraTargetParam); // updateCameraTargetTransform
  char cVar1 = FUN_00481620(); // check if paused or in menu
  if (cVar1 == '\0') {
    FUN_004d3b50(local_1c); // getGameCamera?
    FUN_008abea0(); // followCameraUpdate?
  }
  else {
    // Vtable offset +0xd8: handleInput or some update
    (**(code **)(*thisPtr + 0xd8))(local_1c);
  }
  if (local_1c[0] != 0) {
    (*local_10)(local_1c[0]);
  }
  return;
}