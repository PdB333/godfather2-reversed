// FUNC_NAME: Math::quaternionMultiply
undefined4 Math::quaternionMultiply(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  undefined4 uVar1;
  undefined1 local_f0 [112];
  undefined1 local_80 [124];
  
  uVar1 = FUN_0082acf0(local_80,param_4,param_3);
  FUN_0082ad70(local_f0,uVar1,param_2);
  FUN_0082ac70(param_1,param_3,local_f0);
  return param_1;
}