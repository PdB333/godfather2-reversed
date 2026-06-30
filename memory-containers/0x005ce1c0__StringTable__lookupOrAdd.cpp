// FUNC_NAME: StringTable::lookupOrAdd
int StringTable::lookupOrAdd(char *string, int *outFlags)
{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *unaff_ESI;
  int iVar6;
  int result;
  
  result = -1;
  if (string != (char *)0x0) {
    pcVar2 = string;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 0x1;
    } while (cVar1 != '\0');
    iVar5 = 0;
    if (0 < unaff_ESI[1]) {
      iVar6 = 0;
      do {
        iVar3 = _strncmp((char *)(*unaff_ESI + iVar6), string, (int)pcVar2 - (int)(string + 1));
        if (iVar3 == 0) {
          result = *(int *)(iVar6 + *unaff_ESI + 0x44);
          *outFlags = *(int *)(iVar6 + 0x40 + *unaff_ESI);
        }
        iVar5 = iVar5 + 0x1;
        iVar6 = iVar6 + 0x48;
      } while (iVar5 < unaff_ESI[1]);
      if (result != -1) {
        return result;
      }
    }
  }
  iVar5 = unaff_ESI[1];
  iVar6 = 0;
  if (0 < iVar5) {
    piVar4 = (int *)(*unaff_ESI + 0x44);
    while( true ) {
      iVar3 = piVar4[-1];
      *outFlags = iVar3;
      result = *piVar4;
      if (iVar3 == 1) break;
      iVar6 = iVar6 + 0x1;
      piVar4 = piVar4 + 0x12;
      if (iVar5 <= iVar6) {
        return result;
      }
    }
  }
  return result;
}