// FUNC_NAME: InputManager::isControllerConnected
undefined4 FUN_006904e0(undefined4 param_1,char param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  
  if ((param_2 != '\0') && (param_2 != -1)) {
    cVar1 = FUN_00b930b0(param_2);
    bVar2 = cVar1 != '\0';
    if ((!bVar2) && (*param_3 != '\0')) {
      *param_3 = bVar2;
      return 1;
    }
    *param_3 = bVar2;
  }
  return 0;
}