// FUNC_NAME: StringUtils::hashString
void FUN_005ab9a0(char *param_1)

{
  char cVar1;
  int *unaff_ESI;
  char *local_8;
  int local_4;
  
  cVar1 = *param_1;
  local_8 = param_1;
  while (cVar1 != '\0') {
    local_8 = local_8 + 1;
    cVar1 = *local_8;
  }
  local_4 = unaff_ESI[2] + *unaff_ESI;
  FUN_005aba20(&param_1,&local_8);
  return;
}