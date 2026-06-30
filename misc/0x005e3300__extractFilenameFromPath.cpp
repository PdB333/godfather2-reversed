// FUNC_NAME: extractFilenameFromPath
undefined4 extractFilenameFromPath(char *path)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  char *lastSlash;
  
  if (path != (char *)0x0) {
    cVar2 = *path;
    lastSlash = path;
    while (cVar2 != '\0') {
      if ((cVar2 == '\\') || (cVar2 == '/')) {
        lastSlash = path + 1; // +0x0: track position after last slash
      }
      pcVar1 = path + 1;
      path = path + 1;
      cVar2 = *pcVar1;
    }
    if (lastSlash != (char *)0x0) {
      uVar3 = FUN_004dafd0(); // likely string allocation/duplication
      return uVar3;
    }
  }
  return 0;
}