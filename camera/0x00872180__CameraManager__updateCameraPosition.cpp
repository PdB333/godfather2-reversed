// FUNC_NAME: CameraManager::updateCameraPosition
void __thiscall CameraManager::updateCameraPosition(int this, float *targetPos)
{
  int iVar1;
  float *pfVar2;
  float fVar3;
  double dVar4;
  
  if (*(char *)(this + 0x25) == '\0') {
    iVar1 = FUN_00471610(); // likely getPlayerTransform or getPlayerPosition
    *(undefined8 *)(this + 0x18) = *(undefined8 *)(iVar1 + 0x30); // copy position X,Y
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(iVar1 + 0x38); // copy position Z
    pfVar2 = (float *)FUN_0086d500(); // getCameraOffset or getInputDelta
    *(float *)(this + 0x18) = *pfVar2 * DAT_00d76128 + *(float *)(this + 0x18); // apply offset X
    *(float *)(this + 0x1c) = pfVar2[1] * DAT_00d76128 + *(float *)(this + 0x1c); // apply offset Y
    *(float *)(this + 0x20) = pfVar2[2] * DAT_00d76128 + *(float *)(this + 0x20); // apply offset Z
    *(undefined1 *)(this + 0x25) = 1; // mark initialized
  }
  fVar3 = *targetPos - *(float *)(this + 0x18); // delta X
  if ((DAT_00d5ef84 <= (float)((uint)fVar3 & DAT_00e44680)) ||
     (DAT_00d5ef84 <= (float)((uint)(targetPos[2] - *(float *)(this + 0x20)) & DAT_00e44680))) {
    dVar4 = (double)fVar3;
    FUN_00b9a9fa(); // likely clampAngle or normalizeAngle
    fVar3 = (float)dVar4;
  }
  else {
    fVar3 = 0.0;
  }
  FUN_00871bd0(fVar3); // apply rotation or update camera orientation
  return;
}