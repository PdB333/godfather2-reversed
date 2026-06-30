// FUNC_NAME: CollisionCamera::updateOrbitalPosition
void __fastcall CollisionCamera::updateOrbitalPosition(float *cameraPosition, float *orbitalInput)
{
  // DAT_00e2b1a4 = some constant (e.g., orbit speed or distance)
  // DAT_00e44564 = some constant (e.g., 1.0f or reference distance)
  // param_2[0..3] = quaternion or axis-angle representing orbit rotation
  // param_2[4..7] = 0,0,0,1? (unused, possibly spell or fill)
  
  float invSqLen = orbitalInput[0] * orbitalInput[0] + orbitalInput[1] * orbitalInput[1] + orbitalInput[2] * orbitalInput[2] + orbitalInput[3] * orbitalInput[3];
  float invRatio = DAT_00e2b1a4 / invSqLen;  // some inverse length scaling
  float f4 = DAT_00e44564 - invRatio;        // adjustment factor

  // Call to allocator (returns 4 floats but we interpret as larger area or struct)
  float *resultBuffer = (float *)FUN_00414aa0();  // likely float[8] or struct with 8 floats, e.g., Matrix4x4 or CameraMatrix
  float *base = (float *)((int)resultBuffer);     // reinterpret for offset access

  // Extract original transform from buffer? (cameraPosition +4,+8,+c are offsets into camera data)
  base[3] = DAT_00e44564 - *(float *)((int)base + 0xc);  // some kind of subtraction from constant
  base[0] = f4 * base[0];
  base[1] = f4 * base[1];
  base[2] = f4 * base[2];
  base[3] = f4 * base[3];
  base[4] = DAT_00e44564 - *(float *)((int)base + 0x10);  // also subtract other offsets
  base[5] = DAT_00e44564 - *(float *)((int)base + 0x14);
  base[6] = DAT_00e44564 - *(float *)((int)base + 0x18);
  base[7] = DAT_00e2b1a4;  // store constant at end

  // No explicit return, but function modifies the result buffer that gets returned through resultBuffer pointer
  // (likely caller uses this pointer for further camera math)
}