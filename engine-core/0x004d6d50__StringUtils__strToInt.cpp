// FUNC_NAME: StringUtils::strToInt
void __fastcall strToInt(undefined4 param_1, char *param_2, uint *param_3)
{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  
  bVar2 = 0;
  uVar3 = 0;
  
  // Skip leading whitespace
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    for (; (cVar1 = *param_2, cVar1 == ' ' ||
           (((cVar1 == '\t' || (cVar1 == '\r')) || (cVar1 == '\n')))); param_2 = param_2 + 1) {
    }
    
    // Check for negative sign
    iVar4 = 1;
    if (*param_2 == '-') {
      iVar4 = -1;
      param_2 = param_2 + 1;
    }
    
    // Convert digits
    cVar1 = *param_2;
    while (cVar1 != '\0') {
      if (9 < (int)cVar1 - 0x30U) goto LAB_004d6db7; // non-digit encountered
      param_2 = param_2 + 1;
      uVar3 = ((int)cVar1 - 0x30U) + uVar3 * 10;
      cVar1 = *param_2;
    }
    
    uVar3 = iVar4 * uVar3;
    bVar2 = 1;
  }
  
LAB_004d6db7:
  if (param_3 != (uint *)0x0) {
    *param_3 = -(uint)bVar2 & uVar3; // If bVar2 is 0, store 0; otherwise store the converted value
  }
  return;
}