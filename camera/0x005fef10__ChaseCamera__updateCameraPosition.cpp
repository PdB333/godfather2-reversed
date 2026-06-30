// FUNC_NAME: ChaseCamera::updateCameraPosition
void __fastcall ChaseCamera::updateCameraPosition(float *this)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float in_XMM4_Da; // delta time or frame time
  
  // +0x38: some flag/state (if zero, skip)
  if (this[0x38] == 0.0) {
    return;
  }
  
  // +0x43: another flag/state for horizontal rotation
  if (this[0x43] != 0.0) {
    // +0x44: horizontal rotation angle
    // +0x3b: some factor (speed multiplier?)
    // +0x3c: another factor
    // +0x43: horizontal rotation speed
    this[0x44] =
         (this[0x3b] - (float)((uint)in_XMM4_Da & DAT_00e44680)) * this[0x3c] * this[0x43]
         * DAT_00e2b04c;
  }
  
  fVar3 = DAT_00e44588; // min clamp value
  fVar2 = DAT_00e2cd54; // speed multiplier
  fVar6 = DAT_00e2afac; // max clamp value
  fVar1 = DAT_00e2a848; // step adjustment
  fVar4 = this[0x3f] - this[0x3d]; // target - current vertical angle
  
  // Vertical angle interpolation (pitch)
  if ((fVar4 != 0.0) && (((uint)this[0x2d] >> 6 & 1) == 0)) {
    if (fVar4 <= DAT_00e2afac) {
      if (fVar4 < DAT_00e44588) {
        fVar4 = fVar4 + DAT_00e2a848;
      }
    }
    else {
      fVar4 = fVar4 - DAT_00e2a848;
    }
    fVar4 = this[0x3c] * fVar4 * DAT_00e2cd54 * (this[0x3b] + in_XMM4_Da) + this[0x3d];
    this[0x3e] = fVar4; // current vertical angle
    if (fVar4 <= fVar6) {
      if (fVar3 <= fVar4) goto LAB_005ff016;
      fVar4 = fVar4 + fVar1;
    }
    else {
      fVar4 = fVar4 - fVar1;
    }
    this[0x3e] = fVar4;
  }
LAB_005ff016:
  // Horizontal angle interpolation (yaw)
  if (((uint)this[0x2d] >> 5 & 1) == 0) {
    fVar4 = this[0x40]; // current horizontal angle
    if (this[0x42] != fVar4) { // target != current
      fVar5 = this[0x42] - fVar4;
      if (fVar5 <= fVar6) {
        if (fVar5 < fVar3) {
          fVar5 = fVar5 + fVar1;
        }
      }
      else {
        fVar5 = fVar5 - fVar1;
      }
      fVar4 = fVar5 * (this[0x3b] + in_XMM4_Da) * fVar2 * this[0x3c] + fVar4;
      this[0x41] = fVar4; // interpolated horizontal angle
      if (fVar4 <= fVar6) {
        if (fVar3 <= fVar4) goto LAB_005ff099;
        fVar4 = fVar4 + fVar1;
      }
      else {
        fVar4 = fVar4 - fVar1;
      }
      this[0x41] = fVar4;
    }
  }
LAB_005ff099:
  // Update camera position using velocity
  fVar1 = this[3]; // original z component?
  fVar6 = (this[0x3b] - (float)((uint)in_XMM4_Da & DAT_00e44680)) * this[0x3c];
  fVar6 = fVar6 * fVar6; // squared time factor
  // +0x00-0x03: position (x,y,z,w)
  // +0x34-0x37: velocity components
  *this = fVar6 * this[0x34] + *this;
  this[1] = fVar6 * this[0x35] + this[1];
  this[2] = fVar6 * this[0x36] + this[2];
  this[3] = fVar6 * this[0x37] + this[3];
  this[3] = fVar1; // restore original z?
  return;
}