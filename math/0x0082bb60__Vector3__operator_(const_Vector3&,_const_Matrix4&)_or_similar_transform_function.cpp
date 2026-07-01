// FUNC_NAME: Vector3::operator*(const Vector3&, const Matrix4&) or similar transform function
undefined4 FUN_0082bb60(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  undefined4 uVar1;
  undefined1 local_b0 [80];  // likely Vector4 or Quaternion temp
  undefined1 local_60 [92];  // likely Vector3 temp
  
  // Transform param_4 by param_3 (matrix) -> store in local_b0
  uVar1 = FUN_008365c0(local_b0, param_4, param_3);
  
  // Multiply param_2 by the transformed result -> store in local_60
  uVar1 = FUN_00836650(local_60, param_2, uVar1);
  
  // Final operation: combine param_3 with the result -> store in param_1 (output)
  FUN_00836570(param_1, param_3, uVar1);
  
  return param_1;
}