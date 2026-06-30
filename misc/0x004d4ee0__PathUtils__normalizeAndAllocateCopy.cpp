// FUNC_NAME: PathUtils::normalizeAndAllocateCopy
undefined4 * PathUtils::normalizeAndAllocateCopy(undefined4 *outParam)
{
  uint uVar1;
  char *pcVar2;
  uint *in_EAX;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  
  if (in_EAX[1] != 0) {
    pcVar2 = "\\";
    do {
      pcVar3 = pcVar2;
      pcVar2 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    uVar1 = *in_EAX;
    uVar4 = PathUtils::findLastBackslash(uVar1);
    if (uVar4 != 0) {
      do {
        uVar5 = uVar4;
        uVar4 = PathUtils::findLastBackslash(pcVar3 + (uVar5 - 0xe2f048));
      } while (uVar4 != 0);
      if ((uVar5 != 0) && (uVar1 < uVar5)) {
        outParam[3] = 0;
        PathUtils::copySubstring(uVar1, uVar5 - uVar1);
        return outParam;
      }
    }
  }
  *outParam = 0;
  outParam[1] = 0;
  outParam[2] = 0;
  outParam[3] = 0;
  return outParam;
}