// FUNC_NAME: SomeClass::handleFileTransfer
void __thiscall SomeClass::handleFileTransfer(void* thisPtr, int* tokenPtr)
{
  char* pathStr;
  char c;
  char* start;
  char* local_118;
  int local_114;
  undefined4 local_10c;
  char local_108 [260];

  if ((*tokenPtr == *(int*)((int)thisPtr + 0x14)) && (*(int*)((int)thisPtr + 0x1c) != 0)) {
    FUN_004d3bc0(&DAT_01163cd4); // likely mutex lock / get some global info
    if (local_114 != 0) {
      pathStr = *(char**)((int)thisPtr + 0x1c);
      start = pathStr;
      do {
        c = *start;
        start = start + 1;
      } while (c != '\0');
      if ((int)(start - pathStr) < 0x100) {
        start = pathStr + (int)(start - pathStr - 2); // last character before null
        // scan backwards over trailing digits
        while ((start != pathStr) && ('/' < *start) && (*start < ':')) {
          start = start - 1;
        }
        int prefixLen = (int)(start + 1 - pathStr); // length excluding trailing digits
        if (prefixLen + local_114 + 1 < 0x100) {
          _strncpy(local_108, pathStr, prefixLen);
          local_108[prefixLen] = '\0';
          char* extraStr = local_118;
          if (extraStr == (char*)0x0) {
            extraStr = &DAT_0120546e; // default string
          }
          int extraLen = strlen(extraStr);
          char* dest = (char*)((int)&local_10c + 3); // some buffer after local_10c
          // copy extraStr to dest
          for (int i = 0; i < extraLen / 4; i++) {
            *(undefined4*)dest = *(undefined4*)extraStr;
            dest += 4;
            extraStr += 4;
          }
          for (int i = 0; i < extraLen % 4; i++) {
            *dest = *extraStr;
            dest++;
            extraStr++;
          }
        }
      }
    }
    if (local_118 != (char*)0x0) {
      (*local_10c)(local_118); // call function pointer with string argument
    }
  }
  return;
}