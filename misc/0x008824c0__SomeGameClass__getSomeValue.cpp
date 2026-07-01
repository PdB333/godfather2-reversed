// FUNC_NAME: SomeGameClass::getSomeValue
undefined4 FUN_008824c0(undefined4 param_1, undefined8 *param_2)
{
  undefined **local_18;
  undefined4 local_14;
  undefined8 local_10;
  undefined4 local_8;
  float local_4;
  
  local_18 = &PTR_FUN_00d76e80;
  local_14 = 4;
  local_4 = DAT_00d5ccf8; // Some global float threshold
  FUN_005fcf80(param_1, &local_18, DAT_00d76e70); // Likely a setup/init call
  if (_DAT_00d577a0 <= local_4) { // Compare global value to threshold
    *param_2 = local_10;
    *(undefined4 *)(param_2 + 1) = local_8;
    return 1; // Success
  }
  return 0; // Failure
}