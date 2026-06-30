// FUNC_NAME: EARSCharacter::processRotationAction
undefined1 __thiscall EARSCharacter::processRotationAction(float *inputAngles, int param_3, int param_4)
{
  int iVar1;
  undefined1 result;
  undefined4 local_ec_result[4]; // packed float struct from vtable call
  undefined4 local_104_array[4]; // buffer for function call
  int local_74;
  undefined4 local_b0;
  undefined4 local_a4;
  undefined4 local_84;
  void *local_d4; // pointer to function table
  undefined4 local_d0;
  undefined4 local_b4;
  undefined local_64[96]; // buffer for subsequent call
  
  // Copy input angles (assumed vector of 4 floats, e.g., quaternion)
  float input0 = inputAngles[0];
  float input1 = inputAngles[1];
  float input2 = inputAngles[2];
  float input3 = inputAngles[3];
  
  result = 0;
  
  // Call vtable function at +0x48 to get current local angles (likely also 4 floats)
  (**(code **)(*(int *)this + 0x48))(local_ec_result); // assumes this is the object with vtable
  
  // Pack into local struct for comparison
  // Note: uStack_e4 is same as local_ec_result[0] after call
  undefined4 local_e0 = local_ec_result[0];
  undefined4 local_dc = local_ec_result[1];
  undefined4 local_d8 = local_ec_result[2];
  undefined4 local_d4_val = DAT_00e2b1a4; // global constant
  
  // Check if angle difference (after masking with a bitwise AND) is within threshold
  uint diff_bits = (uint)(input0 - *(float *)&local_e0);
  float masked_diff = (float)(diff_bits & DAT_00e44680); // mask to get absolute??
  if (masked_diff <= *(float *)&DAT_00e2d99c) // threshold constant
  {
    iVar1 = -0x80000000; // INT_MIN as default priority
    if (param_4 != 0)
    {
      iVar1 = param_4; // use provided priority
    }
    result = 1;
    undefined4 global_val = DAT_00e2b1a4; // some global state
    
    // Call function to set up a command (FUN_005425d0)
    FUN_005425d0(local_104_array, &local_e0, 2, iVar1, 0, 0);
    
    // Build a callback structure
    local_b0 = 0xffffffff;
    local_a4 = 0xffffffff;
    void *funcTable = &PTR_FUN_00e32a8c; // pointer to function table
    local_74 = 0;
    local_84 = 0;
    local_d0 = global_val;
    local_b4 = global_val;
    
    // Execute the callback (FUN_009e5ed0) with the structure
    FUN_009e5ed0(local_64, &funcTable);
    
    // If callback returned non-zero, indicate failure
    if (local_74 != 0)
    {
      return 0;
    }
  }
  return result;
}