// FUNC_NAME: String::concatWithSeparator
undefined4 FUN_0082b890(undefined4 this, undefined4 param_2, undefined4 param_3, undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 local_b0 [80];
  undefined1 local_60 [92];
  
  uVar1 = FUN_008251d0(local_b0,param_4,param_3);
  uVar1 = FUN_00825260(local_60,param_2,uVar1);
  FUN_00825180(this,param_3,uVar1);
  return this;
}