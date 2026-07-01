// FUNC_NAME: EARSObject::normalizeVectorAndApplyScale
void EARSObject::normalizeVectorAndApplyScale(int thisPtr, undefined4 param_2)

{
  float *pfVar1;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  pfVar1 = *(float **)(thisPtr + 0xc);
  local_20 = _DAT_00d5780c / SQRT(*pfVar1 * *pfVar1 + pfVar1[1] * pfVar1[1] + pfVar1[2] * pfVar1[2]);
  local_14 = _DAT_00d5780c;
  local_1c = local_20;
  local_18 = local_20;
  FUN_0056b0e0(pfVar1,param_2,&local_20);
  FUN_007f3430(param_2);
  FUN_007f3430(param_2);
  FUN_0056b2a0(&local_20,param_2,param_2);
  return;
}