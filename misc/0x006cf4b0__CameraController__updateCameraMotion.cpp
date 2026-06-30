// FUNC_NAME: CameraController::updateCameraMotion
void __thiscall CameraController::updateCameraMotion(CameraController *this, float dt)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *pPlayerObject;
  float f;
  float velX, velY;
  float targetX, targetY;
  float clampedX, clampedY;
  float lerpFactor;
  float vx, vy;
  float currentX, currentY;
  float smoothX, smoothY;
  float temp;
  undefined4 auStack_20[7]; // 28 bytes

  // Timer at offset 0xa0 controls freeze duration
  if (*(float *)(this + 0xa0) > 0.0f) {
    // Timer is counting down
    dt = *(float *)(this + 0xa0) - dt;
    *(float *)(this + 0xa0) = dt;
    if (dt <= 0.0f) {
      // Timer expired - reset camera
      cVar1 = FUN_0089c630(); // Is camera ready to be reset?
      if (cVar1 != '\0') {
        FUN_00899150(); // Reset camera rotation
        FUN_006d52c0(this + 0x20); // Possibly slerp or clear rotation
      }
      *(undefined4 *)(this + 0xa0) = 0;
      if (*(int *)(this + 0xc) == 0) {
        iVar2 = 0;
      } else {
        iVar2 = *(int *)(this + 0xc) - 0x48; // Offset to get player object
      }
      // Notify game of camera change
      FUN_00424df0(0, iVar2, DAT_00d5c454, 8, 0, 0);
      return;
    }
    // Timer still running, skip update
    return;
  }

  // Timer <= 0: perform normal interpolation
  // Get global game instance for input / state
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar2 = 0;
  } else {
    iVar2 = **(int **)(DAT_012233a0 + 4) - 0x1f30; // Adjust to class base
  }
  uVar3 = (**(code **)(*(int *)(iVar2 + 0x1f30) + 8))(); // Some virtual call
  iVar2 = FUN_00410540(uVar3); // Get player input state?

  // Get camera bounds provider from own 0xc pointer
  if (*(int *)(this + 0xc) == 0) {
    pPlayerObject = (int *)0x0;
  } else {
    pPlayerObject = (int *)(*(int *)(this + 0xc) - 0x48); // Base of player object
  }
  // Call a method on the player object that returns bounds
  (**(code **)(*pPlayerObject + 0x24))(auStack_20);
  iVar4 = FUN_008a01a0(pPlayerObject);
  if (iVar4 != 0) {
    FUN_00899180(); // Early exit handler
    return;
  }

  // Check some flags on the player input state
  if ((((*(byte *)(iVar2 + 0x10) & 0x40) != 0) && ((*(byte *)(iVar2 + 0x12) & 0x40) == 0)) &&
     (*(int *)(DAT_0112a838 + 0x5c) == 0)) {
    // Set freeze timer if conditions met
    *(float *)(this + 0xa0) = DAT_00d5c454;
  }

  if (*(float *)(this + 0xa0) > 0.0f) {
    // Timer was set, skip further update (deferred to next frame)
    return;
  }

  // Main interpolation logic
  cVar1 = FUN_00410f30(); // Check some game mode?
  if (cVar1 != '\0') {
    lerpFactor = 0.0f; // Override to instant
  } else {
    lerpFactor = DAT_00d5c454; // Normal damping factor
  }

  // Read velocity components from input state (iVar2)
  vx = *(float *)(iVar2 + 8);
  if ((float)((uint)vx & DAT_00e44680) > lerpFactor) {
    // If magnitude > lerpFactor, zero it? Actually it's a sign mask; likely checks absolute value.
    // Probably: if (fabs(vx) > EPS) keep vx, else zero.
    // Decompiler shows: if ((float)((uint)vx & DAT_00e44680) > fVar9) then fVar6=0.
    // So we implement: if (fabs(vx) > lerpFactor) then vx = 0.0f? But the decompiler uses fVar6, which is later used.
    // Let's follow the decompiled flow exactly.
    vx = 0.0f;
  }
  vy = 0.0f;
  if (lerpFactor < (float)((uint)*(float *)(iVar2 + 0xc) & DAT_00e44680)) {
    vy = *(float *)(iVar2 + 0xc);
  }

  // Multiply by global speed factor
  f = _DAT_00d5780c;
  if (DAT_0112a7a5 != '\0') {
    f = DAT_00d5ccf8; // Alternative speed factor
  }
  vx = f * vx;
  f = _DAT_00d5780c;
  if (DAT_0112a7a4 != '\0') {
    f = DAT_00d5ccf8;
  }
  vy = f * vy;

  // Check another game mode
  cVar1 = FUN_00410eb0();
  if (cVar1 != '\0') {
    vy *= DAT_00d5d934;
    vx *= DAT_00d5d934;
  }

  // Multiply by player's "zoom" or scale factor from pPlayerObject[0x2c]
  targetX = (float)pPlayerObject[0x2c] * vx * dt + *(float *)(this + 0x80);
  targetY = *(float *)(this + 0x84) - (float)pPlayerObject[0x2c] * vy * dt;
  *(float *)(this + 0x80) = targetX;
  *(float *)(this + 0x84) = targetY;

  // Clamp target positions using bounds from player object
  f = DAT_00e44598; // Some threshold or mask
  temp = (float)pPlayerObject[0x28]; // minX?
  clampedX = targetX;
  if (targetX < temp) {
    clampedX = temp;
  }
  temp = (float)pPlayerObject[0x29]; // maxX?
  if ((clampedX <= temp) && (temp = targetX, targetX < (float)pPlayerObject[0x28])) {
    temp = (float)pPlayerObject[0x28];
  }
  *(float *)(this + 0x80) = temp;

  temp = (float)pPlayerObject[0x2a]; // minY?
  if ((f < (float)((uint)temp & DAT_00e44680)) || (f < (float)(pPlayerObject[0x2b] & DAT_00e44680))) {
    // Some condition based on bit masks
    f = targetY;
    if (targetY < temp) {
      f = temp;
    }
    temp = (float)pPlayerObject[0x2b]; // maxY?
    if ((f <= temp) && (temp = (float)pPlayerObject[0x2a], (float)pPlayerObject[0x2a] <= targetY)) {
      temp = targetY;
    }
    *(float *)(this + 0x84) = temp;
  }

  // Lerp current rotation toward target rotation
  lerpFactor = DAT_00d5c454;
  // Smooth interpolation of rotation angles (offsets appear to be rotation quaternion or euler)
  // Offsets: +0x60,0x64,0x68,0x6c are target rotation; +0x20,0x24,0x28,0x2c are current rotation; +0x40,0x44,0x48,0x4c are smoothed output?
  f = (*(float *)(this + 100) - *(float *)(this + 0x24)) * lerpFactor;
  // Note: +100 = 0x64, (this+0x24) is part of current rotation
  temp = (*(float *)(this + 0x68) - *(float *)(this + 0x28)) * lerpFactor;
  float temp2 = (*(float *)(this + 0x6c) - *(float *)(this + 0x2c)) * lerpFactor;
  *(float *)(this + 0x20) = (*(float *)(this + 0x60) - *(float *)(this + 0x20)) * lerpFactor + *(float *)(this + 0x20);
  *(float *)(this + 0x24) = f + *(float *)(this + 0x24);
  *(float *)(this + 0x28) = temp + *(float *)(this + 0x28);
  *(float *)(this + 0x2c) = temp2 + *(float *)(this + 0x2c);
  // Now lerp the smoothed rotation toward the target velocity? Actually it's interpolating the smoothed rotation toward the computed target (0x80,0x84)
  *(float *)(this + 0x40) = (*(float *)(this + 0x80) - *(float *)(this + 0x40)) * lerpFactor + *(float *)(this + 0x40);
  *(float *)(this + 0x44) = (*(float *)(this + 0x84) - *(float *)(this + 0x44)) * lerpFactor + *(float *)(this + 0x44);
  *(float *)(this + 0x48) = (*(float *)(this + 0x88) - *(float *)(this + 0x48)) * lerpFactor + *(float *)(this + 0x48);
  *(float *)(this + 0x4c) = (*(float *)(this + 0x8c) - *(float *)(this + 0x4c)) * lerpFactor + *(float *)(this + 0x4c);

  // If in a specific mode, immediately snap smoothed rotation to target
  cVar1 = FUN_00410eb0();
  if (cVar1 != '\0') {
    *(float *)(this + 0x40) = *(float *)(this + 0x80);
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(this + 0x84);
    *(undefined4 *)(this + 0x48) = *(undefined4 *)(this + 0x88);
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(this + 0x8c);
  }

  return;
}