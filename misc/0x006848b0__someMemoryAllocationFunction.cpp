// FUNC_NAME: someMemoryAllocationFunction
undefined4 FUN_006848b0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  iVar1 = FUN_0043b980(0x60,&local_c,param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_00906040(param_1);
    return uVar2;
  }
  return 0;
}