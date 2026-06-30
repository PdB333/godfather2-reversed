// FUNC_NAME: StringUtils::trimQuotes
uint StringUtils::trimQuotes(void)
{
  char cVar1;
  char cVar2;
  uint in_EAX;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  int *unaff_EDI;
  
  pcVar5 = (char *)*unaff_EDI; // +0x00: string buffer pointer
  uVar3 = in_EAX & 0xffffff00;
  pcVar6 = pcVar5;
  if (pcVar5 != (char *)0x0) {
    // Skip leading whitespace
    for (; ((((cVar1 = *pcVar6, cVar1 == ' ' || (cVar1 == '\n')) || (cVar1 == '\t')) ||
            ((cVar1 == '\r' || (cVar1 == '\f')))) || (cVar1 == '\v')); pcVar6 = pcVar6 + 1) {
    }
    cVar1 = *pcVar6;
    // Check if string is quoted with single or double quotes
    if ((cVar1 == '\"') || (cVar1 == '\'')) {
      // Find end of string (last character before trailing whitespace)
      for (pcVar5 = pcVar5 + unaff_EDI[1] + -1; // +0x04: string length
          (((cVar2 = *pcVar5, cVar2 == ' ' || (cVar2 == '\n')) || (cVar2 == '\t')) ||
          (((cVar2 == '\r' || (cVar2 == '\f')) || (cVar2 == '\v')))); pcVar5 = pcVar5 + -1) {
      }
      // If matching quote found and there's content between quotes
      if ((*pcVar5 == cVar1) && (pcVar6 < pcVar5)) {
        pcVar5 = pcVar5 + (-1 - (int)pcVar6);
        iVar4 = 0;
        if (0 < (int)pcVar5) {
          // Shift content left to remove quotes
          do {
            *(char *)(iVar4 + *unaff_EDI) = pcVar6[iVar4 + 1];
            iVar4 = iVar4 + 1;
          } while (iVar4 < (int)pcVar5);
        }
        iVar4 = *unaff_EDI;
        pcVar5[iVar4] = '\0';
        unaff_EDI[1] = (int)pcVar5; // Update length
        uVar3 = CONCAT31((int3)((uint)iVar4 >> 8),1);
      }
    }
  }
  return uVar3;
}