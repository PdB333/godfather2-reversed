// FUNC_NAME: swapUint64Pair
void __fastcall swapUint64Pair(undefined8 *param_1)
{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 *in_EAX;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = *in_EAX;
  param_1[1] = in_EAX[1];
  *in_EAX = uVar1;
  in_EAX[1] = uVar2;
  return;
}