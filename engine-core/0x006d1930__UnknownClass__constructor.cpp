// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00473950(param_2);
  *this = &PTR_FUN_00d5f360;
  this[2] = &PTR_LAB_00d5f358;
  this[0x2b] = 0;
  this[0x2a] = 0;
  this[0x29] = 0;
  this[0x28] = 0;
  this[0x23] = 0;
  this[0x22] = 0;
  this[0x21] = 0;
  this[0x20] = 0;
  puVar2 = (undefined4 *)FUN_009c8f80();
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  puVar2 = (undefined4 *)(**(code **)*puVar2)(0xa0,&local_c);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    *puVar2 = &PTR_LAB_00d5f2f4;
  }
  this[0x36] = puVar2;
  uVar3 = (**(code **)(*param_2 + 0x28))();
  this[0x35] = uVar3;
  this[0x39] = 0;
  cVar1 = FUN_0089c630();
  if (cVar1 != '\\0') {
    FUN_006913c0(8);
  }
  return this;
}