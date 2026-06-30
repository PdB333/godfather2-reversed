// FUNC_NAME: String::set
void __thiscall String::set(int this, char *newStr)
{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pcVar4 = *(char **)(this + 0x20); // +0x20: string buffer pointer
  if (pcVar4 == (char *)0x0) {
    pcVar2 = (char *)0x0;
  }
  else {
    pcVar2 = pcVar4;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = pcVar2 + (1 - (int)(pcVar4 + 1));
  }
  if (newStr != (char *)0x0) {
    pcVar3 = newStr;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = pcVar3 + (1 - (int)(newStr + 1));
    if (pcVar2 < pcVar3) {
      if (pcVar4 != (char *)0x0) {
        (**(code **)(*DAT_01194538 + 4))(pcVar4,0); // free old buffer
        *(undefined4 *)(this + 0x20) = 0;
      }
      local_c = 2;
      local_8 = 0x10;
      local_4 = 0;
      pcVar4 = (char *)(**(code **)*DAT_01194538)(pcVar3,&local_c); // allocate new buffer
      *(char **)(this + 0x20) = pcVar4;
      if (pcVar4 == (char *)0x0) {
        return;
      }
      do {
        cVar1 = *newStr;
        *pcVar4 = cVar1;
        newStr = newStr + 1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      return;
    }
    if (pcVar3 != (char *)0x0) {
      do {
        cVar1 = *newStr;
        *pcVar4 = cVar1;
        newStr = newStr + 1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      return;
    }
  }
  if (pcVar4 != (char *)0x0) {
    (**(code **)(*DAT_01194538 + 4))(pcVar4,0);
    *(undefined4 *)(this + 0x20) = 0;
  }
  return;
}