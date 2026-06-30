// FUNC_NAME: SomeClass::getTransformMatrix
void __thiscall getTransformMatrix(int this, int outMatrix, undefined4 *outScale)
{
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  // Call virtual function at vtable+0x18 (likely getWorldTransform or similar)
  (**(code **)(**(int **)(this + 0x18) + 0x18))();
  
  // Copy the transform matrix (4x3 or 4x4) from local stack to output
  *(undefined4 **)outMatrix = &local_30;
  *(undefined4 *)(outMatrix + 4) = local_30;
  *(undefined4 *)(outMatrix + 8) = uStack_2c;
  
  // Copy scale vector (3 floats) to output
  *outScale = uStack_24;
  outScale[1] = uStack_20;
  outScale[2] = uStack_1c;
  
  return;
}