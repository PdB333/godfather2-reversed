// FUNC_NAME: Matrix3x3::buildOrthonormalBasis
void __thiscall Matrix3x3::buildOrthonormalBasis(float *outMatrix, float *forward, float *up)
{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float crossX;
  float crossY;
  float crossZ;
  int local_14;
  
  // _DAT_00d5780c appears to be a global constant, likely (float)1.0 or similar
  // DAT_00d5ef84 appears to be another global constant
  fVar1 = _DAT_00d5780c;
  
  // Copy forward vector into matrix columns 2 and 3 (rows 0-2)
  // Matrix layout: outMatrix[0..2]=right, [3..5]=up, [6..8]=forward? 
  // Actually looking at indices: +8=forward.x, +9=forward.y, +10=forward.z
  *(undefined8 *)(outMatrix + 8) = *(undefined8 *)forward;  // copy forward.x and forward.y
  fVar2 = DAT_00d5ef84;
  outMatrix[10] = forward[2];  // forward.z
  
  // Scale forward by fVar2 and add up vector to get position offset?
  outMatrix[0xc] = forward[0] * fVar2;
  outMatrix[0xd] = forward[1] * fVar2;
  outMatrix[0xe] = forward[2] * fVar2;
  outMatrix[0xc] = outMatrix[0xc] + up[0];
  outMatrix[0xd] = outMatrix[0xd] + up[1];
  outMatrix[0xe] = outMatrix[0xe] + up[2];
  
  // Compute right vector as cross product of (some zero vector?) and forward
  // This looks like: right = cross(up, forward) where up may have 0 in some components
  crossX = outMatrix[9] * 0.0 - outMatrix[10] * fVar1;
  crossY = outMatrix[10] * 0.0 - outMatrix[8] * 0.0;
  crossZ = outMatrix[8] * fVar1 - outMatrix[9] * 0.0;
  outMatrix[0] = crossX;
  outMatrix[1] = crossY;
  outMatrix[2] = crossZ;
  
  // Normalize right vector using FUN_0056afa0 (likely vector length)
  local_14 = 0;
  fVar3 = (float10)FUN_0056afa0(&crossX, &crossX);  // returns length
  outMatrix[0] = crossX;
  outMatrix[1] = crossY;
  outMatrix[2] = crossZ;
  
  if (fVar3 <= (float10)0.0f) {
    // If right vector is zero length, recompute using different cross product
    crossX = outMatrix[9] * 0.0 - outMatrix[10] * 0.0;
    crossY = outMatrix[10] * _DAT_00d5780c - outMatrix[8] * 0.0;
    crossZ = outMatrix[8] * 0.0 - outMatrix[9] * _DAT_00d5780c;
    outMatrix[0] = crossX;
    outMatrix[1] = crossY;
    outMatrix[2] = crossZ;
    local_14 = 0;
    FUN_0056afa0(&crossX, &crossX);
    outMatrix[0] = crossX;
    outMatrix[1] = crossY;
    outMatrix[2] = crossZ;
  }
  
  // Compute up vector as cross product of right and forward
  outMatrix[4] = outMatrix[1] * outMatrix[10] - outMatrix[2] * outMatrix[9];
  outMatrix[5] = outMatrix[2] * outMatrix[8] - outMatrix[0] * outMatrix[10];
  outMatrix[6] = outMatrix[0] * outMatrix[9] - outMatrix[1] * outMatrix[8];
  
  return;
}