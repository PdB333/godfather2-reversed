// FUNC_NAME: Language::languageCodeToId
undefined4 languageCodeToId(char *languageCode, size_t codeLength)

{
  int iVar1;
  
  iVar1 = __strnicmp("cs",languageCode,codeLength);
  if (iVar1 != 0) {
    iVar1 = __strnicmp("cz",languageCode,codeLength);
    if (iVar1 != 0) {
      iVar1 = __strnicmp("nl",languageCode,codeLength);
      if (iVar1 == 0) {
        return 8;
      }
      iVar1 = __strnicmp("fr",languageCode,codeLength);
      if (iVar1 == 0) {
        return 2;
      }
      iVar1 = __strnicmp("de",languageCode,codeLength);
      if (iVar1 == 0) {
        return 3;
      }
      iVar1 = __strnicmp("it",languageCode,codeLength);
      if (iVar1 == 0) {
        return 4;
      }
      iVar1 = __strnicmp("pl",languageCode,codeLength);
      if (iVar1 == 0) {
        return 5;
      }
      iVar1 = __strnicmp("ru",languageCode,codeLength);
      if (iVar1 == 0) {
        return 6;
      }
      iVar1 = __strnicmp("es",languageCode,codeLength);
      if (iVar1 == 0) {
        return 7;
      }
      __strnicmp("en",languageCode,codeLength);
      return 0;
    }
  }
  return 1;
}