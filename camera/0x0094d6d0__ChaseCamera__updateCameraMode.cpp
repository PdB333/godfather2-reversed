// FUNC_NAME: ChaseCamera::updateCameraMode
void __fastcall ChaseCamera::updateCameraMode(ChaseCamera *this)
{
  int cameraMode = *(int *)((int)this + 0x50); // +0x50: camera mode enum
  if (cameraMode == 1) {
    // Drive mode camera
    FUN_0094d200((int)this + 0x58, &DAT_00e568d0); // +0x58: camera offset data
    return;
  }
  if (cameraMode != 2) {
    // Default / walk mode camera
    FUN_0094d200((int)this + 0x58, &DAT_00e5689c);
    return;
  }
  // Combat mode camera
  FUN_0094d200((int)this + 0x58, &DAT_00e56904);
}