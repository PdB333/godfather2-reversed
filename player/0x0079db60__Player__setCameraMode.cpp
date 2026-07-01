// FUNC_NAME: Player::setCameraMode
void __thiscall Player::setCameraMode(int thisPtr, int mode)
{
  char isActive;
  undefined4 *cameraData;
  
  isActive = FUN_00481620(); // likely some game state check (e.g., isPlayerAlive)
  if (isActive != '\0') {
    if (mode == 1) {
      cameraData = (undefined4 *)(thisPtr + 0x2060); // +0x2060: first-person camera data
    }
    else if (mode == 2) {
      cameraData = (undefined4 *)(thisPtr + 0x2090); // +0x2090: third-person camera data
    }
    else {
      if (mode != 3) {
        return;
      }
      cameraData = (undefined4 *)(thisPtr + 0x20c0); // +0x20c0: cinematic camera data
    }
    if (cameraData != (undefined4 *)0x0) {
      // Copy camera transform (16 bytes = 4 floats/vec4)
      *(undefined4 *)(thisPtr + 0x2db0) = *cameraData;       // +0x2db0: camera position x
      *(undefined4 *)(thisPtr + 0x2db4) = cameraData[1];     // +0x2db4: camera position y
      *(undefined4 *)(thisPtr + 0x2db8) = cameraData[2];     // +0x2db8: camera position z
      *(undefined4 *)(thisPtr + 0x2dbc) = cameraData[3];     // +0x2dbc: camera orientation w
      FUN_006d9da0(); // likely updateCameraTransform or applyCamera
      FUN_00424ea0(*(undefined4 *)(&DAT_00002494 + thisPtr), thisPtr + 0x2d90, 0); // setCameraFOV or similar
    }
  }
  return;
}