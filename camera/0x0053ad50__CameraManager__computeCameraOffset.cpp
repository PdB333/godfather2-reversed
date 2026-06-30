// FUNC_NAME: CameraManager::computeCameraOffset
undefined4 __thiscall CameraManager::computeCameraOffset(int this, float *outOffset, float t, float *inOffset)
{
  float fVar1;
  double dVar2;
  
  // Interpolate between two camera height values (likely min/max height) based on t
  fVar1 = (*(float *)(this + 0x34) - *(float *)(this + 0x30)) * t +
          *(float *)(this + 0x30);
  // X component: scale input offset X by interpolated height
  *outOffset = *inOffset * fVar1;
  // Y component: always zero (no lateral offset)
  outOffset[1] = 0.0;
  // Z component: compute with additional scaling factors
  dVar2 = (double)(*(float *)(this + 0x38) * fVar1);
  FUN_00b99fcb(); // likely sin/cos or math helper
  outOffset[2] = (float)dVar2 * *(float *)(this + 0x3c) * inOffset[2];
  FUN_00414aa0(); // likely another math helper or cleanup
  return 1;
}