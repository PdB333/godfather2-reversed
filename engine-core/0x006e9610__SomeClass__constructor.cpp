// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_011298cc = this;
  this[3] = 0;
  this[1] = &PTR_FUN_00e2f19c;
  this[2] = 1;
  this[4] = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  this[5] = param_3;
  *this = &PTR_FUN_00d5fd04;
  this[1] = &PTR_LAB_00d5fcf4;
  FUN_006e9060(param_2, param_3, &local_c);
  (**(code **)(*(int *)this[5] + 8))();
  return this;
}