// FUNC_NAME: PathParser::extractSubstringAfterLastDelimiter
undefined4 * __thiscall PathParser::extractSubstringAfterLastDelimiter(int *pThis, undefined4 *outBuffer, char *inputPath)
{
  char *delimiterPtr;
  char currentChar;
  int *delimiterRef;
  int lastDelimiterPos;
  int tempPos;
  
  // pThis[0] = pointer to a delimiter string (e.g., "/" or "\\")
  // pThis[1] = length of the part to copy (e.g., total buffer size)
  int partLength = pThis[1];
  
  if (partLength != 0) {
    // Find end of input path
    delimiterPtr = inputPath + 1;
    do {
      currentChar = *inputPath;
      inputPath = inputPath + 1;
    } while (currentChar != '\0');
    
    // Get the base pointer from this (likely a delimiter string pointer)
    delimiterRef = (int *)*pThis;
    lastDelimiterPos = (int)findNextDelimiter((char *)delimiterRef);
    
    if (lastDelimiterPos != 0) {
      do {
        tempPos = lastDelimiterPos;
        lastDelimiterPos = (int)findNextDelimiter(inputPath + (tempPos - (int)delimiterPtr));
      } while (lastDelimiterPos != 0);
      
      // tempPos now holds the address of the last delimiter found
      if ((tempPos != 0) && (inputPath[tempPos - (int)delimiterPtr] != '\0')) {
        // Clear the fourth dword of output buffer (null terminator for a 16-byte buffer)
        outBuffer[3] = 0;
        // Copy the substring starting at the last delimiter position
        // Length = (base pointer - start of substring) + partLength
        stringCopy(inputPath + (tempPos - (int)delimiterPtr),
                   (int)((char *)delimiterRef - (inputPath + (tempPos - (int)delimiterPtr))) + partLength);
        return outBuffer;
      }
    }
  }
  
  // Failure case: zero out the output buffer
  outBuffer[0] = 0;
  outBuffer[1] = 0;
  outBuffer[2] = 0;
  outBuffer[3] = 0;
  return outBuffer;
}