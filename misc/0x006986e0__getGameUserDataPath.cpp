// FUNC_NAME: getGameUserDataPath
// Address: 0x006986e0
// Role: Reads registry to get user data directory and constructs path "EA Games\<GameFolder>"

undefined4 getGameUserDataPath(void)
{
  char cResult;
  char *pcStr;
  undefined4 uResult;
  undefined4 uFolderName;
  char szRegValue[64];

  uFolderName = 9; // Default folder ID (maybe "The Godfather II")
  cResult = readRegistryString(0, L"SOFTWARE\\EA Games\\The Godfather II", L"locale", szRegValue, 0x40);
  if (cResult != '\0') {
    pcStr = szRegValue;
    do {
      cResult = *pcStr;
      pcStr = pcStr + 1;
    } while (cResult != '\0');
    if (1 < (uint)((int)pcStr - (int)(szRegValue + 1))) {
      uFolderName = convertRegPathToWide(szRegValue, 2);
    }
  }
  uResult = getLocalizedGameFolderName(uFolderName);
  formatWideString(&g_wszUserDataPath, 0x104, L"%ws\\%ws", L"EA Games", uResult);
  return uFolderName;
}