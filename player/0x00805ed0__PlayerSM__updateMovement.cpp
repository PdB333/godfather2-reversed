// FUNC_NAME: PlayerSM::updateMovement
void __thiscall PlayerSM::updateMovement(int *this, uint inputFlags)
{
  char bIsPaused;
  float *pPosition;
  int iTargetIndex;
  float dx, dy, dz, distSq;
  float localPos[3];
  
  // Check if game is paused or disabled
  bIsPaused = FUN_00481640();
  if (bIsPaused) {
    this[0x129] = this[0x129] | 1;   // +0x484 -> pause flag bit0
  }
  
  // Update input state from external source
  FUN_0054f860(inputFlags);
  
  // Get current camera/character position (x,y,z)
  pPosition = (float *)FUN_00555290();
  localPos[0] = *pPosition;
  localPos[1] = pPosition[1];
  localPos[2] = pPosition[2];
  
  // Check if we should adjust position towards AI target
  bIsPaused = FUN_00481660();  // another pause/state check
  if (bIsPaused) {
    iTargetIndex = FUN_00471610();  // get current AI target entity
    if (iTargetIndex) {
      dx = localPos[0] - *(float *)(iTargetIndex + 0x30);  // target position X
      dy = localPos[1] - *(float *)(iTargetIndex + 0x34);  // target position Y
      dz = localPos[2] - *(float *)(iTargetIndex + 0x38);  // target position Z
      distSq = dz*dz + dy*dy + dx*dx;
      if (distSq <= DAT_00e44598)  // distance threshold (squared)
        goto SKIP_MOVEMENT_ADJUST;
    }
  }
  FUN_0046f7b0(localPos);  // apply movement adjustment (e.g., move towards target)
  
SKIP_MOVEMENT_ADJUST:
  // Call update on sub-component at offset +0x8dc (this+0x237*4)
  (**(code **)(*this + 0xdc))(this + 0x237);
  // Another virtual method (no args)
  (**(code **)(*this + 0x2d4))();
  
  // Check if we should trigger a specific effect (e.g., footstep, muzzle flash)
  if ( (inputFlags != 0) &&
       ((~this[0x129] & 1) != 0) &&    // +0x484 bit0 not set
       ((uint)this[0x124] >> 0xf & 1) != 0 )  // +0x490 bit15 set (some input flag)
  {
    bIsPaused = FUN_00481620();  // check if effect allowed
    if (bIsPaused) {
      (**(code **)(*this + 0x288))(2, 0, 0);  // trigger effect (type 2)
    }
  }
  
  // Update team/faction ID if changed
  iTargetIndex = 0;
  if (this[0x108] != -0x1e98fd1) {  // +0x420 team ID sentinel
    iTargetIndex = FUN_00405af0(this[0x108]);  // resolve to new ID
  }
  if ((iTargetIndex != this[0x7b9]) && (iTargetIndex != 0)) {  // +0x1ee4 cached ID
    (**(code **)(*this + 0x2f0))(iTargetIndex);  // notify of team change
    this[0x7b9] = iTargetIndex;
  }
  return;
}