// FUNC_NAME: FUN_005f8d30
void __thiscall FUN_005f8d30(int this, float param2, float param3)
{
  float *local_18;
  int local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_005f8c90();
  local_18 = &PTR_LAB_00e407e8;
  local_10 = param2 * *(float *)(this + 0x18) + param3;
  local_c = *(undefined4 *)(this + 0x10);
  param3 = param2 * *(float *)(this + 0x18) + param3;
  local_8 = 0;
  local_4 = *(undefined4 *)(this + 0x14);
  local_14 = this;
  FUN_005fcf80(&local_c, &local_18, param3 * param3);
  return;
}