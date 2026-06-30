// FUNC_NAME: resolvePathOrIdentifier
void __thiscall resolvePathOrIdentifier(char *inputPath, int defaultIndex, int *outIndex, char *outBuffer, char **outPointer)
{
  int localVar_EAX;
  int parsedValue;
  char *bufferPtr;
  char currentChar;
  
  // Initialize output buffer to empty
  *outBuffer = 0;
  
  // If path starts with '/', treat as absolute path relative to some base
  if (*inputPath == '/') {
    defaultIndex = *(int *)(**(int **)(DAT_0119a9cc + 0x2514) + 0x60); // +0x60 is likely some base index
    inputPath = inputPath + 1;
  }
  
  *outIndex = defaultIndex;
  
LAB_005ad1d0:
  bufferPtr = &DAT_01226f58; // Static buffer for parsing tokens (0x1226f58)
  do {
    currentChar = *inputPath;
    switch(currentChar) {
    case '\0': // End of string
      *bufferPtr = '\0';
      if (localVar_EAX == 0) {
        localVar_EAX = defaultIndex;
      }
      *outIndex = localVar_EAX;
      if (outPointer == (char **)0x0) {
        // Copy parsed buffer to output
        bufferPtr = &DAT_01226f58;
        do {
          currentChar = *bufferPtr;
          (outBuffer + (-0x1226f58))[(int)bufferPtr] = currentChar; // Copies from static buffer to outBuffer
          bufferPtr = bufferPtr + 1;
        } while (currentChar != '\0');
        return;
      }
      *outPointer = &DAT_01226f58;
      return;
      
    case '.': // Possibly parent directory ".."
      if (inputPath[1] != '.') goto switchD_005ad1e6_caseD_2f;
      *bufferPtr = currentChar;
      currentChar = inputPath[1];
      bufferPtr = bufferPtr + 1;
      inputPath = inputPath + 1;
      
    default:
      *bufferPtr = currentChar;
      bufferPtr = bufferPtr + 1;
      inputPath = inputPath + 1;
      break;
      
    case '/': // Path separator
      goto switchD_005ad1e6_caseD_2f;
      
    case ':': // Namespace separator
      *bufferPtr = '\0';
      parsedValue = FUN_005bc230(&DAT_01226f58); // Likely resolves a name to an ID
      localVar_EAX = 0;
      if (parsedValue != 0) {
        *outIndex = parsedValue;
        if (outPointer == (char **)0x0) {
          inputPath = inputPath + 1;
          parsedValue = (int)outBuffer - (int)inputPath;
          do {
            currentChar = *inputPath;
            inputPath[parsedValue] = currentChar;
            inputPath = inputPath + 1;
          } while (currentChar != '\0');
          return;
        }
        *outPointer = inputPath + 1;
        return;
      }
      inputPath = inputPath + 1;
      goto LAB_005ad1d0;
    }
  } while( true );
  
switchD_005ad1e6_caseD_2f:
  // Handle path components separated by '/'
  *bufferPtr = '\0';
  defaultIndex = FUN_005bc230(&DAT_01226f58);
  localVar_EAX = 0;
  if (defaultIndex == 0) {
    *outIndex = 0;
    if (outPointer == (char **)0x0) {
      return;
    }
    *outPointer = 0;
    return;
  }
  inputPath = inputPath + 1;
  goto LAB_005ad1d0;
}