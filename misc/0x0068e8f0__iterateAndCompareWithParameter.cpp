// FUNC_NAME: iterateAndCompareWithParameter
bool iterateAndCompareWithParameter(int param_1)

{
  char cVar1;
  int *piVar2;
  undefined **local_14;
  int local_10;
  undefined4 local_c;
  
  local_10 = 0;
  local_c = 7;
  local_14 = &PTR_LAB_00d5c86c;
  FUN_00495960(); // beginIteration
  cVar1 = FUN_00495980(); // hasNext
  while (cVar1 != '\0') {
    piVar2 = (int *)FUN_004959c0(); // getNext
    (**(code **)(*piVar2 + 0x14))(&local_14); // call virtual function at vtable+0x14
    cVar1 = FUN_00495980(); // hasNext
  }
  return local_10 == param_1;
}