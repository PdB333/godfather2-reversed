// FUNC_NAME: SmoothValue::update
void __fastcall SmoothValue::update(int *this)
{
  float fVar1;
  float fVar2;
  
  if (this[1] == 1) {
    // Linear interpolation mode
    fVar2 = ((float)this[5] / (float)this[3]) * (DAT_01205228 - (float)this[6]) +
            (float)this[2];
  }
  else {
    // Exponential smoothing mode
    fVar2 = (float)this[2] - (DAT_01205228 - (float)this[6]) / (float)this[4];
  }
  this[2] = fVar2;
  fVar1 = _DAT_00d5780c; // Maximum value (clamp upper bound)
  if (_DAT_00d5780c <= fVar2) {
    *this = 1; // State: finished/complete
    this[2] = fVar1;
    this[6] = DAT_01205228; // Reset timer
    return;
  }
  if (fVar2 <= 0.0) {
    *this = 0; // State: idle/stopped
    this[2] = 0;
  }
  this[6] = DAT_01205228; // Update timestamp
  return;
}