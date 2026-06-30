// FUNC_NAME: SomeCameraClass::getPosition
void __thiscall SomeCameraClass::getPosition(int this, float *outPos)
{
  float fVar1;
  float fVar2;
  float local_30;
  float fStack_2c;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  
  // Call virtual function at vtable+0x18 (likely getTransform or getViewMatrix)
  (**(code **)(**(int **)(this + 0x18) + 0x18))();
  
  // Combine and scale the position components
  // The local variables appear to be components of a 4x4 matrix or quaternion
  fVar1 = (fStack_20 + local_30) * DAT_00e2cd54;  // Scale factor (likely world units conversion)
  fVar2 = (fStack_1c + fStack_2c) * DAT_00e2cd54;
  
  // Extract position from the matrix/transform
  // fStack_24 + &local_30 is likely the translation component (x)
  *outPos = (fStack_24 + (float)&local_30) * DAT_00e2cd54;
  outPos[1] = fVar1;  // y
  outPos[2] = fVar2;  // z
  
  return;
}