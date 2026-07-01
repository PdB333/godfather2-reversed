// FUNC_NAME: Player::updateCameraShake
void __fastcall Player::updateCameraShake(int this)
{
  int iVar1;
  int iVar2;
  undefined4 local_50[16]; // stack buffer for camera shake data
  
  FUN_00471340(); // likely getCurrentTime or updateTime
  iVar1 = FUN_00471610(); // likely getPlayerCamera or getActiveCamera
  if (*(int **)(this + 0x184) != (int *)0x0) {
    iVar2 = (**(code **)(**(int **)(this + 0x184) + 0x14))(); // check if shake is active
    if (iVar2 == 1) {
      local_50[8] = *(undefined4 *)(iVar1 + 0x30); // camera position/offset X
      local_50[9] = *(undefined4 *)(iVar1 + 0x34); // camera position/offset Y
      local_50[0] = 0; // shake intensity or duration
      local_50[1] = 0;
      local_50[2] = 0;
      local_50[3] = 0;
      local_50[5] = 0;
      local_50[6] = 0;
      local_50[7] = 0;
      local_50[4] = 0;
      local_50[10] = *(undefined4 *)(iVar1 + 0x38); // camera position/offset Z
      local_50[12] = _DAT_00d5780c; // global shake intensity or frequency
      local_50[4] = _DAT_00d5780c;
      local_50[11] = _DAT_00d5780c;
      local_50[15] = _DAT_00d5780c;
      FUN_004b59d0(iVar1, &local_50); // applyCameraShake
      FUN_009f17c0(&local_50); // releaseShakeData
    }
  }
  return;
}