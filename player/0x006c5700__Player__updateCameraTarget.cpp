// FUNC_NAME: Player::updateCameraTarget
void __fastcall Player::updateCameraTarget(int this)
{
  undefined4 cameraMode;
  
  cameraMode = getCameraMode();
  setCameraTarget(cameraMode, this + 0x2a0, this + 0x29c, this + 0x2a4);
  return;
}