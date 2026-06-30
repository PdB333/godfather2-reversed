// FUNC_NAME: ChaseCamera::updateCameraPosition
float __thiscall ChaseCamera::updateCameraPosition(uint *this, float deltaTime, float param_3)
{
  float fVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  uint local_20[7];
  
  uVar2 = (uint)(param_3 * param_3 <= 0.0);
  if (uVar2 != *this) {
    if (uVar2 == 1) {
      // Transition to "locked" state - reset camera position
      FUN_006daa50(); // likely resetCameraState
      this[8] = this[0x10]; // +0x20: targetPosition
      this[9] = 0;          // +0x24: velocity
      this[10] = 0;         // +0x28: acceleration
      this[0xb] = 0;        // +0x2c: some flag
    }
    *this = uVar2; // +0x00: state flag (0 = free, 1 = locked)
  }
  if (*this == 0) {
    // Free camera mode - interpolate position
    fVar1 = (float)this[0x13]; // +0x4c: maxPosition
    fVar3 = (float)this[0x11] * param_3 + (float)this[0x10]; // +0x44: speed * param_3 + currentPosition
    fVar4 = DAT_00e44564 - fVar1; // some global min bound
    this[0x10] = (uint)fVar3; // +0x40: currentPosition
    if (fVar3 < fVar4) {
      this[0x12] = this[0x14]; // +0x48: reset velocity to some default
      this[0x10] = (uint)fVar4;
      return (float10)(float)this[0x10];
    }
    if (fVar1 < fVar3) {
      fVar3 = fVar1;
    }
    this[0x10] = (uint)fVar3;
    this[0x12] = this[0x14]; // +0x48: reset velocity
    return (float10)(float)this[0x10];
  }
  // Locked camera mode - decelerate and check for stop
  fVar1 = (float)this[0x12]; // +0x48: velocity
  this[0x12] = (uint)(fVar1 - deltaTime); // decelerate
  if ((fVar1 - deltaTime <= 0.0) &&
     ((float)this[0x10] * (float)this[0x10] <= (float)this[0x15] * (float)this[0x15])) {
    // Stopped and within threshold - snap to target
    local_20[0] = 0;
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[3] = 0;
    FUN_006daac0(local_20, deltaTime); // likely snapToTarget
    this[0x10] = local_20[0]; // +0x40: set position to snapped value
  }
  return (float10)(float)this[0x10];
}