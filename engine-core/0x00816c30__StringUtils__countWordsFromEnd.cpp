// FUNC_NAME: StringUtils::countWordsFromEnd
char* StringUtils::countWordsFromEnd(uint maxWordCount, undefined4* stringInfo)
{
  char cVar1;
  bool bVar2;
  char* result;
  int iVar4;
  uint wordCount;
  uint charCount;
  char* currentPos;
  char* strStart;
  
  strStart = (char *)*stringInfo;
  result = (char *)0x0;
  if (strStart == (char *)0x0) {
    strStart = &DAT_0120546e; // empty string fallback
  }
  currentPos = strStart + stringInfo[1] + -1; // start from end of string (stringInfo[1] = length)
  bVar2 = false;
  wordCount = 0;
  charCount = 0;
  do {
    if (currentPos < strStart) {
      return result;
    }
    cVar1 = *currentPos;
    if ((((cVar1 == ' ') || (cVar1 == '\\n')) || (cVar1 == '\\t')) ||
       (((cVar1 == '\\r' || (cVar1 == '\\f')) || (cVar1 == '\\v')))) {
      if (bVar2) {
        if (charCount < 4) {
          iVar4 = 1;
        }
        else if (charCount < 8) {
          iVar4 = 2;
        }
        else {
          iVar4 = (-(uint)(0xc < charCount) & 2) + 3;
        }
        wordCount = wordCount + iVar4;
        if (maxWordCount < wordCount) {
          return result;
        }
        charCount = 0;
        bVar2 = false;
        result = currentPos;
      }
    }
    else {
      bVar2 = true;
      charCount = charCount + 1;
    }
    currentPos = currentPos + -1;
  } while( true );
}