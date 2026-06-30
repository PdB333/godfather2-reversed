// FUNC_NAME: StringUtils::formatAndLog
void StringUtils::formatAndLog(undefined4 param_1)

{
  char *in_EAX;
  undefined4 uVar1;
  undefined4 local_14;
  undefined2 local_10;
  undefined2 local_e;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_14 = 0;
  local_10 = 0;
  local_e = 0;
  if ((in_EAX != (char *)0x0) && (*in_EAX != '\0')) {
    uVar1 = FUN_004dafd0(); // likely getStringLength or formatString
    FUN_00408260(&local_14,uVar1); // likely string copy or concatenation
  }
  local_c = local_14;
  local_8 = param_1;
  local_4 = 0;
  FUN_00408a00(&local_c,0); // likely log output function
  FUN_00408310(&local_14); // likely string destructor or cleanup
  return;
}