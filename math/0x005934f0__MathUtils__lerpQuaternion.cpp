// FUNC_NAME: MathUtils::lerpQuaternion
undefined4 * MathUtils::lerpQuaternion(undefined4 *result, int param_2)

{
  undefined4 in_EAX;
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  float fStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float fStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;
  
  if (*(int *)(param_2 + 4) == *(int *)(param_2 + 8)) {
    puVar1 = (undefined4 *)FUN_00593410(result,in_EAX);
    return puVar1;
  }
  if ((float)((uint)(DAT_00e44564 - *(float *)(param_2 + 0xc)) & DAT_00e44680) < DAT_00e2e780) {
    puVar1 = (undefined4 *)FUN_00593410(result,in_EAX);
    return puVar1;
  }
  if ((float)((uint)(DAT_00e2b1a4 - *(float *)(param_2 + 0xc)) & DAT_00e44680) < DAT_00e2e780) {
    puVar1 = (undefined4 *)FUN_00593410(result,in_EAX);
    return puVar1;
  }
  uStack_48 = 0;
  uStack_4c = 0;
  local_50 = 0;
  fStack_44 = DAT_00e2b1a4;
  uStack_38 = 0;
  uStack_3c = 0;
  local_40 = 0;
  fStack_34 = DAT_00e2b1a4;
  uStack_28 = 0;
  uStack_2c = 0;
  local_30 = 0;
  fStack_24 = DAT_00e2b1a4;
  uStack_18 = 0;
  uStack_1c = 0;
  local_20 = 0;
  fStack_14 = DAT_00e2b1a4;
  iVar2 = FUN_00593410(&local_50,in_EAX);
  iVar3 = FUN_00593410(&local_30,in_EAX);
  if (iVar2 != 0) {
    if (iVar3 != 0) {
      FUN_005781f0(result,*(undefined4 *)(param_2 + 0xc));
      return result;
    }
    *result = local_50;
    result[1] = uStack_4c;
    result[2] = uStack_48;
    result[3] = fStack_44;
    result[4] = local_40;
    result[5] = uStack_3c;
    result[6] = uStack_38;
    result[7] = fStack_34;
    return result;
  }
  if (iVar3 != 0) {
    *result = local_30;
    result[1] = uStack_2c;
    result[2] = uStack_28;
    result[3] = fStack_24;
    result[4] = local_20;
    result[5] = uStack_1c;
    result[6] = uStack_18;
    result[7] = fStack_14;
    return result;
  }
  return (undefined4 *)0x0;
}