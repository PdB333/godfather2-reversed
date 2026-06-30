// FUNC_NAME: parseGuidString
uint parseGuidString(char *param_1)

{
  char cVar1;
  uint in_EAX;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  
  uVar2 = in_EAX & 0xffffff00;
  if ((param_1 != (char *)0x0) && (*param_1 == '{')) {
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if ((int)pcVar3 - (int)(param_1 + 1) == 0x26) {
      uVar4 = 0;
      uVar2 = (int)"{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}" - (int)param_1;
      pcVar3 = param_1;
      do {
        cVar1 = *pcVar3;
        if (pcVar3[uVar2] == 'X') {
          if ((((cVar1 < '0') || ('9' < cVar1)) && ((cVar1 < 'A' || ('F' < cVar1)))) &&
             (5 < (byte)(cVar1 + 0x9fU))) break;
        }
        else if (pcVar3[uVar2] != cVar1) break;
        cVar1 = param_1[uVar4 + 1];
        if (pcVar3[(int)("{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}" + (1 - (int)param_1))] == 'X') {
          if (((cVar1 < '0') || ('9' < cVar1)) &&
             (((cVar1 < 'A' || ('F' < cVar1)) && ((cVar1 < 'a' || ('f' < cVar1)))))) {
LAB_004d949e:
            uVar4 = uVar4 + 1;
            break;
          }
        }
        else if (pcVar3[(int)("{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}" + (1 - (int)param_1))] !=
                 cVar1) goto LAB_004d949e;
        uVar4 = uVar4 + 2;
        pcVar3 = pcVar3 + 2;
      } while (uVar4 < 0x26);
      if (uVar4 == 0x26) {
        return CONCAT31((int3)(uVar2 >> 8),1);
      }
    }
    uVar2 = uVar2 & 0xffffff00;
  }
  return uVar2;
}