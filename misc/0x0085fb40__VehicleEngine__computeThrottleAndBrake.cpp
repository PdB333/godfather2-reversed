// FUNC_NAME: VehicleEngine::computeThrottleAndBrake
void __thiscall computeThrottleAndBrake(int *this, float *outThrottle, float *outBrake, float param4, uint inputFlags)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar6 = _DAT_00d5780c; // +0x0: some global speed constant (max vehicle speed?)
  iVar1 = this[0x3cc]; // +0xF30: transmission gear index
  if ((1 < iVar1) && (((uint)this[0x3ca] >> 0x16 & 1) != 0)) { // +0x3CA: bitfield? Check reverse gear bit 0x16
    FUN_0085fa40(outThrottle, outBrake, param4, (float)this[0x445] - (float)this[0x444], _DAT_00d7575c); // +0x444: RPM low, +0x445: RPM high
    return;
  }
  if (iVar1 < 1) { // Neutral or reverse?
    if (this[0x44c] == 1) { // +0x44C: some gear state flag?
      if (iVar1 < 1) goto LAB_0085fdf4; // Handbrake?
      goto LAB_0085fc4d;
    }
    fVar3 = (float)(inputFlags & DAT_00e44680); // Input throttle magnitude
    if (fVar3 < DAT_00d756e0) { // Dead zone threshold
      fVar3 = (_DAT_00d5780c - fVar3 * _DAT_00d75848) * *outThrottle;
      *outThrottle = fVar3;
      if (0.0 < fVar3) {
        if (fVar6 <= fVar3) {
          fVar3 = fVar6;
        }
        *outThrottle = fVar3;
      }
      else {
        *outThrottle = 0.0;
      }
      goto LAB_0085fdf4;
    }
    // Reverse throttle region
    fVar3 = fVar3 * _DAT_00d65228;
    *outThrottle = 0.0;
    *outBrake = fVar3;
    if (fVar3 <= 0.0) {
      *outBrake = 0.0;
      goto LAB_0085fdf4;
    }
  }
  else {
LAB_0085fc4d: // Forward gear logic
    fVar3 = (float)this[0x445]; // RPM high (current engine speed?)
    fVar4 = (float)this[0x444]; // RPM low (idle?)
    if (fVar3 - fVar4 <= 0.0) goto LAB_0085fdf4; // Engine not running?
    // Get current velocity and position difference?
    FUN_00875190(&local_18,0); // Get vehicle velocity (x component?)
    FUN_0085ecf0(&local_c); // Get vehicle position (x component?)
    param4 = (float)(this[0x3cd] & DAT_00e44680); // +0x3CD: input throttle (unsigned)
    fVar6 = _DAT_00d5780c;
    if (param4 <= _DAT_00d75844) goto LAB_0085fdf4; // Dead zone check
    if (_DAT_00d6bf98 < param4) { // Max throttle clamp
      param4 = _DAT_00d6bf98;
    }
    fVar2 = (float10)(**(code **)(*this + 0x1b8))(); // Virtual function call (get rotation speed?)
    fVar6 = _DAT_00d5780c;
    fVar5 = (float)this[999] * _DAT_00d7583c; // +0xF9C: some tuning factor (engine drag?)
    fVar3 = (float)(((float10)param4 * (float10)_DAT_00d75840 * fVar2) /
                   (float10)(SQRT((local_10 - local_4) * (local_10 - local_4) +
                                  (local_14 - local_8) * (local_14 - local_8) +
                                  (local_18 - local_c) * (local_18 - local_c)) + (fVar3 - fVar4)));
    // Compute torque factor based on engine RPM and vehicle speed
    if (fVar3 <= fVar5) {
      if ((float)this[999] * _DAT_00d75838 < fVar3) { // Coasting threshold
        *outThrottle = 0.0;
        fVar6 = _DAT_00d5780c;
      }
      else {
        fVar4 = (float)this[999] * _DAT_00d75834; // Another tuning factor (engine braking?)
        if ((fVar4 < fVar3) &&
           (fVar3 = _DAT_00d5780c -
                    (_DAT_00d5780c / ((float)this[999] * _DAT_00d75838 - fVar4)) *
                    (fVar3 - fVar4), fVar3 < *outThrottle)) {
          *outThrottle = fVar3; // Reduce throttle for engine braking simulation
        }
      }
      goto LAB_0085fdf4;
    }
    // Above max engine speed - apply brake??
    fVar3 = (fVar3 - fVar5) + _DAT_00d5cf70;
    *outThrottle = 0.0;
    *outBrake = fVar3;
    if (fVar3 <= 0.0) {
      *outBrake = 0.0;
      goto LAB_0085fdf4;
    }
  }
  // Clamp brake output to max speed
  if (fVar6 <= fVar3) {
    fVar3 = fVar6;
  }
  *outBrake = fVar3;
LAB_0085fdf4:
  // Apply input-based deceleration (coasting/braking)
  if (DAT_00d756e0 < (float)(inputFlags & DAT_00e44680)) {
    fVar4 = fVar6 - (float)(inputFlags & DAT_00e44680) * _DAT_00d65228;
    fVar3 = DAT_00d5f520;
    if ((DAT_00d5f520 < fVar4) && (fVar3 = fVar4, fVar6 <= fVar4)) {
      fVar3 = fVar6;
    }
    fVar6 = *outThrottle;
    if (fVar6 <= 0.0) {
      *outThrottle = 0.0;
      return;
    }
    if (fVar6 < fVar3) {
      fVar3 = fVar6;
    }
    *outThrottle = fVar3;
  }
  return;
}