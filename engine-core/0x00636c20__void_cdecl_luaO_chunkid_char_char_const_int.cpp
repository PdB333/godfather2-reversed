// Xbox PDB: void __cdecl luaO_chunkid(char *,char const *,int)
// FUNC_NAME: StringUtils::formatStringWithPrefix
void StringUtils::formatStringWithPrefix(char *dest, char *src)
{
  char cVar1;
  size_t in_EAX;
  char *pcVar2;
  size_t _Count;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (*src == '=') {
    _strncpy(dest,src + 1,in_EAX);
    dest[in_EAX - 1] = '\0';
    return;
  }
  if (*src != '@') {
    _Count = _strcspn(src,"\n");
    *(undefined8 *)dest = s__string___00e42298._0_8_;
    if ((int)(in_EAX - 0x11) < (int)_Count) {
      _Count = in_EAX - 0x11;
    }
    *(undefined2 *)(dest + 8) = s__string___00e42298._8_2_;
    pcVar2 = src;
    if (src[_Count] == '\0') {
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      uVar3 = (int)pcVar2 - (int)src;
      pcVar2 = dest + -1;
      do {
        pcVar5 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
      } while (*pcVar5 != '\0');
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)src;
        src = src + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar2 = *src;
        src = src + 1;
        pcVar2 = pcVar2 + 1;
      }
    }
    else {
      _strncat(dest,src,_Count);
      pcVar2 = dest + -1;
      do {
        pcVar5 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
      } while (*pcVar5 != '\0');
      *(undefined4 *)pcVar2 = DAT_00e42294;
    }
    pcVar2 = dest + -1;
    do {
      pcVar5 = pcVar2;
      pcVar2 = pcVar5 + 1;
    } while (pcVar5[1] != '\0');
    *(undefined2 *)(pcVar5 + 1) = DAT_00e422a4;
    pcVar5[3] = DAT_00e422a6;
    return;
  }
  pcVar5 = src + 1;
  pcVar2 = pcVar5;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  *dest = '\0';
  pcVar6 = pcVar5;
  if ((int)(in_EAX - 8) < (int)pcVar2 - (int)(src + 2)) {
    pcVar5 = pcVar5 + (((int)pcVar2 - (int)(src + 2)) - (in_EAX - 8));
    pcVar2 = dest + -1;
    do {
      pcVar6 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
    } while (*pcVar6 != '\0');
    *(undefined4 *)pcVar2 = DAT_00e42294;
    pcVar6 = pcVar5;
  }
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  dest = dest + -1;
  do {
    pcVar2 = dest + 1;
    dest = dest + 1;
  } while (*pcVar2 != '\0');
  pcVar2 = pcVar6;
  for (uVar3 = (uint)((int)pcVar5 - (int)pcVar6) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)dest = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    dest = dest + 4;
  }
  for (uVar3 = (int)pcVar5 - (int)pcVar6 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *dest = *pcVar2;
    pcVar2 = pcVar2 + 1;
    dest = dest + 1;
  }
  return;
}