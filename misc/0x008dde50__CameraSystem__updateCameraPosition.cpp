// FUNC_NAME: CameraSystem::updateCameraPosition
void __fastcall CameraSystem::updateCameraPosition(int this)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if ((((*(byte *)(this + 0x14) & 3) == 0) && (**(int **)(DAT_012233a0 + 4) != 0)) &&
     (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    iVar2 = FUN_00471610(); // getPlayerTransform
    if (((DAT_00e44598 <
          (float)((uint)(*(float *)(this + 0x18) - *(float *)(iVar2 + 0x30)) & DAT_00e44680)) ||
        (DAT_00e44598 <
         (float)((uint)(*(float *)(this + 0x1c) - *(float *)(iVar2 + 0x34)) & DAT_00e44680))) ||
       (DAT_00e44598 <
        (float)((uint)(*(float *)(this + 0x20) - *(float *)(iVar2 + 0x38)) & DAT_00e44680))) {
      uVar3 = 0;
      do {
        iVar1 = *(int *)(*(int *)(this + 0x24) + 4 + uVar3); // +0x24: cameraList array
        if ((iVar1 != 0) && (iVar1 != 0x48)) {
          FUN_008dc7b0((undefined8 *)(iVar2 + 0x30)); // updateCameraTransform
        }
        uVar3 = uVar3 + 0xc;
      } while (uVar3 < 300);
    }
    *(undefined8 *)(this + 0x18) = *(undefined8 *)(iVar2 + 0x30); // +0x18: cameraPosition
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(iVar2 + 0x38); // +0x20: cameraRotation
  }
  return;
}