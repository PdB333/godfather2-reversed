// FUNC_NAME: StringHash::setHashFromString
void __thiscall StringHash::setHashFromString(uint *this, char *str)
{
  char cVar1;
  uint hash;
  char *pcVar3;
  char buf [24];
  
  if (str != (char *)0x0) {
    pcVar3 = str;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (0x17 < (int)pcVar3 - (int)(str + 1)) {
      hash = FUN_004dafd0(str,str + ((int)pcVar3 - (int)(str + 1)) + -0xf);
      _sprintf(buf,"%08x%s",hash);
    }
    FUN_004eadc0();
    return;
  }
  this[2] = 0;  // +0x08: hash value
  this[3] = 0;  // +0x0C: hash value (64-bit?)
  *this = 0;    // +0x00: string pointer
  this[1] = 0;  // +0x04: string length
  return;
}