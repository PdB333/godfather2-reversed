// FUNC_NAME: ThrowableItem::calcLaunchVector
undefined4 __thiscall ThrowableItem::calcLaunchVector(int this, float *outVector, float interpolationFactor, float *inVector)
{
  float fVar1;
  double dVar2;
  
  // Interpolate between minForce (+0x30) and maxForce (+0x34) based on interpolationFactor
  // +0x30: minForce
  // +0x34: maxForce
  fVar1 = (*(float *)(this + 0x34) - *(float *)(this + 0x30)) * interpolationFactor + *(float *)(this + 0x30);
  
  // Compute x component: scale inVector[0] by interpolated force
  *outVector = *inVector * fVar1;
  
  // y component is always zero (horizontal only)
  outVector[1] = 0.0f;
  
  // Compute z component using vertical multiplier (+0x38) and height multiplier (+0x3c)
  // The double conversion may be to avoid precision loss in the engine's math library
  dVar2 = (double)(*(float *)(this + 0x38) * fVar1);
  // Likely a math helper (e.g., sin/cos) – exact purpose unknown
  FUN_00b99fcb();
  // +0x3c: heightMultiplier (scales final z)
  outVector[2] = (float)dVar2 * *(float *)(this + 0x3c) * inVector[2];
  
  // Another math helper (may finalize or clamp)
  FUN_00414aa0();
  
  return 1; // success
}