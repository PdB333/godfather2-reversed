// FUNC_NAME: SomeClass::setSomeData
void SomeClass::setSomeData(undefined4 param_1, undefined8 *param_2)
{
  int local_4;
  
  FUN_008b3d60(&local_4, &param_1);
  if (local_4 != 0) {
    FUN_008b3dc0(&local_4, &param_1);
    *(undefined8 *)(local_4 + 8) = *param_2;
    *(undefined4 *)(local_4 + 0x10) = *(undefined4 *)(param_2 + 1);
  }
  return;
}