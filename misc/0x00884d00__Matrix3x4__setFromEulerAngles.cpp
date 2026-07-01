// FUNC_NAME: Matrix3x4::setFromEulerAngles
void __thiscall Matrix3x4::setFromEulerAngles(int this, int eulerOrder, int rotationOrder, float inputAngle)
{
  float clampedAngle;
  EulerAngles angles;
  Matrix3x4 rotMatrix;
  Matrix3x4 *matrixPtr;

  // Clamp angle to 0.._DAT_00d5780c range, defaulting to 0 if input is out of range
  clampedAngle = 0.0;
  if ((inputAngle <= 0.0) || (clampedAngle = _DAT_00d5780c, _DAT_00d5780c <= inputAngle)) {
    inputAngle = clampedAngle;
  }
  
  // Build Euler angles from the input parameters
  FUN_0056db60(inputAngle, eulerOrder, rotationOrder, &angles);
  
  // Convert Euler angles to rotation matrix
  FUN_0056dc20(&angles, &rotMatrix);
  
  // Copy rotation matrix fields to this object
  matrixPtr = (Matrix3x4 *)(this + 0x80);
  *matrixPtr = rotMatrix;  // Copy entire matrix (12 floats, 48 bytes)
  
  // Individual field copies (redundant with struct assignment)
  *(float *)(this + 0x84) = rotMatrix.m01;
  *(float *)(this + 0x88) = rotMatrix.m02;
  *(float *)(this + 0x90) = rotMatrix.m10;
  *(float *)(this + 0x94) = rotMatrix.m11;
  *(float *)(this + 0x98) = rotMatrix.m12;
  *(float *)(this + 0xa0) = rotMatrix.m20;
  *(float *)(this + 0xa4) = rotMatrix.m21;
  *(float *)(this + 0xa8) = rotMatrix.m22;
  *(float *)(this + 0xb0) = rotMatrix.m30;
  *(float *)(this + 0xb4) = rotMatrix.m31;
  *(float *)(this + 0xb8) = rotMatrix.m32;
  
  // Normalize the resulting rotation matrix
  FUN_0043a2a0(matrixPtr, matrixPtr);
}