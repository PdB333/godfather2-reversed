// FUNC_NAME: StringTable::addString
int __thiscall StringTable::addString(char *param_1, char *param_2, char *param_3)
{
  int iVar1;
  int in_EAX;
  int iVar2;
  char *_Dest;
  
  iVar1 = *(int *)(in_EAX + 0xa8); // +0xa8: currentCount (number of strings stored)
  _Dest = (char *)(iVar1 * 0x60 + *(int *)(in_EAX + 0xb0)); // +0xb0: stringBuffer (base pointer to string storage)
  *(int *)(in_EAX + 0xa8) = iVar1 + 1; // increment count
  iVar2 = 0;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    _strncpy(_Dest,param_1,0x1f); // copy first string (max 31 chars)
    iVar2 = 0x1f;
  }
  _Dest[iVar2] = '\0'; // null-terminate
  iVar2 = 0;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    _strncpy(_Dest + 0x20,param_2,0x1f); // copy second string at offset 0x20
    iVar2 = 0x1f;
  }
  (_Dest + 0x20)[iVar2] = '\0'; // null-terminate
  if (param_3 == (char *)0x0) {
    iVar2 = 1;
  }
  else {
    iVar2 = __stricmp(param_3,"(none)"); // check if third string is "(none)"
  }
  if (iVar2 == 0) {
    _Dest[0x40] = '\0'; // clear third string slot
    return iVar1;
  }
  iVar2 = 0;
  if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
    _strncpy(_Dest + 0x40,param_3,0x1f); // copy third string at offset 0x40
    iVar2 = 0x1f;
  }
  (_Dest + 0x40)[iVar2] = '\0'; // null-terminate
  return iVar1; // return index of added string
}