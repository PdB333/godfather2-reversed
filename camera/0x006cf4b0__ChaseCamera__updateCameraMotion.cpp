// FUNC_NAME: ChaseCamera::updateCameraMotion
void __thiscall ChaseCamera::updateCameraMotion(ChaseCamera *this, float deltaTime)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined1 auStack_20 [28];
  
  if (*(float *)(this + 0xa0) <= 0.0) { // +0xA0 = m_transitionTimer
    if (**(int **)(DAT_012233a0 + 4) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
    }
    uVar3 = (**(code **)(*(int *)(iVar2 + 0x1f30) + 8))(); // Get player controller
    iVar2 = FUN_00410540(uVar3); // Get player entity
    if (*(int *)(this + 0xc) == 0) { // +0xC = m_targetEntity
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)(*(int *)(this + 0xc) + -0x48); // Get target entity base
    }
    (**(code **)(*piVar5 + 0x24))(auStack_20); // Get target position
    iVar4 = FUN_008a01a0(piVar5); // Check if target is dead
    fVar9 = DAT_00d5c454; // Smoothing factor
    if (iVar4 != 0) {
      FUN_00899180(); // Handle death camera
      return;
    }
    if ((((*(byte *)(iVar2 + 0x10) & 0x40) != 0) && ((*(byte *)(iVar2 + 0x12) & 0x40) == 0)) &&
       (*(int *)(DAT_0112a838 + 0x5c) == 0)) {
      *(float *)(this + 0xa0) = DAT_00d5c454; // Start transition
    }
    if (*(float *)(this + 0xa0) <= 0.0) {
      cVar1 = FUN_00410f30(); // Check if aiming
      if (cVar1 != '\0') {
        fVar9 = 0.0;
      }
      fVar6 = *(float *)(iVar2 + 8); // Player input X
      if ((float)((uint)fVar6 & DAT_00e44680) <= fVar9) {
        fVar6 = 0.0;
      }
      fVar11 = 0.0;
      if (fVar9 < (float)((uint)*(float *)(iVar2 + 0xc) & DAT_00e44680)) {
        fVar11 = *(float *)(iVar2 + 0xc); // Player input Y
      }
      fVar9 = _DAT_00d5780c; // Camera sensitivity
      if (DAT_0112a7a5 != '\0') {
        fVar9 = DAT_00d5ccf8; // Inverted Y
      }
      fVar9 = fVar9 * fVar6;
      fVar6 = _DAT_00d5780c;
      if (DAT_0112a7a4 != '\0') {
        fVar6 = DAT_00d5ccf8; // Inverted X
      }
      fVar6 = fVar6 * fVar11;
      cVar1 = FUN_00410eb0(); // Check if using controller
      if (cVar1 != '\0') {
        fVar6 = fVar6 * DAT_00d5d934; // Controller sensitivity multiplier
        fVar9 = fVar9 * DAT_00d5d934;
      }
      fVar7 = (float)piVar5[0x2c] * fVar6 * deltaTime + *(float *)(this + 0x80); // +0x80 = m_desiredYaw
      fVar10 = *(float *)(this + 0x84) - (float)piVar5[0x2c] * fVar9 * deltaTime; // +0x84 = m_desiredPitch
      *(float *)(this + 0x80) = fVar7;
      *(float *)(this + 0x84) = fVar10;
      fVar6 = DAT_00e44598; // Min/max pitch clamp
      fVar9 = (float)piVar5[0x28]; // Min pitch
      fVar11 = fVar7;
      if (fVar7 < fVar9) {
        fVar11 = fVar9;
      }
      fVar8 = (float)piVar5[0x29]; // Max pitch
      if ((fVar11 <= fVar8) && (fVar8 = fVar7, fVar7 < fVar9)) {
        fVar8 = fVar9;
      }
      *(float *)(this + 0x80) = fVar8;
      fVar9 = (float)piVar5[0x2a]; // Min yaw
      if ((fVar6 < (float)((uint)fVar9 & DAT_00e44680)) ||
         (fVar6 < (float)(piVar5[0x2b] & DAT_00e44680))) {
        fVar6 = fVar10;
        if (fVar10 < fVar9) {
          fVar6 = fVar9;
        }
        fVar11 = (float)piVar5[0x2b]; // Max yaw
        if ((fVar6 <= fVar11) && (fVar11 = fVar9, fVar9 <= fVar10)) {
          fVar11 = fVar10;
        }
        *(float *)(this + 0x84) = fVar11;
      }
      fVar9 = DAT_00d5c454; // Smoothing factor
      fVar6 = (*(float *)(this + 100) - *(float *)(this + 0x24)) * DAT_00d5c454; // +0x64 = m_targetYaw, +0x24 = m_currentYaw
      fVar11 = (*(float *)(this + 0x68) - *(float *)(this + 0x28)) * DAT_00d5c454; // +0x68 = m_targetPitch, +0x28 = m_currentPitch
      fVar7 = (*(float *)(this + 0x6c) - *(float *)(this + 0x2c)) * DAT_00d5c454; // +0x6C = m_targetRoll, +0x2C = m_currentRoll
      *(float *)(this + 0x20) = // +0x20 = m_currentX
           (*(float *)(this + 0x60) - *(float *)(this + 0x20)) * DAT_00d5c454 + // +0x60 = m_targetX
           *(float *)(this + 0x20);
      *(float *)(this + 0x24) = fVar6 + *(float *)(this + 0x24);
      *(float *)(this + 0x28) = fVar11 + *(float *)(this + 0x28);
      *(float *)(this + 0x2c) = fVar7 + *(float *)(this + 0x2c);
      *(float *)(this + 0x40) = // +0x40 = m_currentFOV
           (*(float *)(this + 0x80) - *(float *)(this + 0x40)) * fVar9 + // +0x80 = m_desiredFOV
           *(float *)(this + 0x40);
      *(float *)(this + 0x44) = // +0x44 = m_currentNearPlane
           (*(float *)(this + 0x84) - *(float *)(this + 0x44)) * fVar9 +
           *(float *)(this + 0x44);
      *(float *)(this + 0x48) = // +0x48 = m_currentFarPlane
           (*(float *)(this + 0x88) - *(float *)(this + 0x48)) * fVar9 +
           *(float *)(this + 0x48);
      *(float *)(this + 0x4c) = // +0x4C = m_currentAspect
           (*(float *)(this + 0x8c) - *(float *)(this + 0x4c)) * fVar9 +
           *(float *)(this + 0x4c);
      cVar1 = FUN_00410eb0(); // Check if using controller
      if (cVar1 != '\0') {
        *(float *)(this + 0x40) = *(float *)(this + 0x80); // Snap to desired values
        *(undefined4 *)(this + 0x44) = *(undefined4 *)(this + 0x84);
        *(undefined4 *)(this + 0x48) = *(undefined4 *)(this + 0x88);
        *(undefined4 *)(this + 0x4c) = *(undefined4 *)(this + 0x8c);
      }
    }
  }
  else {
    deltaTime = *(float *)(this + 0xa0) - deltaTime; // Decrease transition timer
    *(float *)(this + 0xa0) = deltaTime;
    if (deltaTime <= 0.0) {
      cVar1 = FUN_0089c630(); // Check if transition complete
      if (cVar1 != '\0') {
        FUN_00899150(); // Finalize transition
        FUN_006d52c0(this + 0x20); // Reset camera position
      }
      *(undefined4 *)(this + 0xa0) = 0;
      if (*(int *)(this + 0xc) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(this + 0xc) + -0x48;
      }
      FUN_00424df0(0,iVar2,DAT_00d5c454,8,0,0); // Notify target of camera change
      return;
    }
  }
  return;
}