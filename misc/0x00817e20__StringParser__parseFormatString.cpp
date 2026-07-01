// FUNC_NAME: StringParser::parseFormatString
// Address: 0x00817e20
// Parses a format string looking for [s=...] tokens and extracts structured data.
// Returns 1 if any token was found, 0 otherwise.
// param_1: input format string
// param_2: pointer to output array structure (offset +0x00: data pointer, +0x04: count, +0x08: capacity)

undefined1 StringParser::parseFormatString(char *inputString, int *outputArray)
{
  undefined8 *dataEntry;
  char currentChar;
  int compareResult;
  char *scanPos;
  char *writePos;
  char *tokenStart;
  char *endBracket;
  undefined1 result;
  undefined1 tokenData_low;
  undefined1 tokenData_high;
  undefined2 tokenData_word;
  undefined4 tokenData_dword1;
  undefined4 tokenData_dword2;
  
  currentChar = *inputString;
  result = 0;
  scanPos = inputString;
  writePos = inputString;
  
  while (currentChar != '\0') {
    if (*scanPos == '[') {
      tokenData_dword1 = 0;
      tokenData_dword2 = 0;
      tokenStart = scanPos + 1;
      tokenData_low = 0x2b;  // '+'
      tokenData_high = 0x2b; // '+'
      
      compareResult = __strnicmp(tokenStart, "s=", DAT_00e53e08);
      if (compareResult == 0) {
        tokenStart = tokenStart + DAT_00e53e08;
        endBracket = _strchr(tokenStart, 0x5d); // ']'
        if (endBracket != (char *)0x0) {
          FUN_00817a50(tokenStart, &tokenData_low); // Parse token value
          result = 1;
          
          if (scanPos != inputString) {
            if (outputArray[1] == 0) {
              FUN_00817cc0(); // Initialize output buffer
            }
            FUN_00817dc0(); // Prepare for writing
            FUN_004d3ea0(writePos, (int)scanPos - (int)writePos); // Copy preceding text
          }
          
          int currentCount = outputArray[1];
          if (outputArray[2] == currentCount) {
            int newCapacity;
            if (currentCount == 0) {
              newCapacity = 1;
            }
            else {
              newCapacity = currentCount * 2;
            }
            FUN_00817810(newCapacity); // Reallocate output array
          }
          
          dataEntry = (undefined8 *)(*outputArray + outputArray[1] * 0xc);
          outputArray[1] = outputArray[1] + 1;
          
          if (dataEntry != (undefined8 *)0x0) {
            *dataEntry = CONCAT44(tokenData_dword1, CONCAT22(tokenData_word, CONCAT11(tokenData_high, tokenData_low)));
            *(undefined4 *)(dataEntry + 1) = tokenData_dword2;
          }
          
          writePos = endBracket + 1;
          scanPos = endBracket;
        }
      }
    }
    scanPos = scanPos + 1;
    currentChar = *scanPos;
  }
  
  FUN_00817dc0(); // Finalize writing
  FUN_004d3ea0(writePos, (int)scanPos - (int)writePos); // Copy remaining text
  
  if (outputArray[1] == 0) {
    FUN_00817cc0(); // Initialize if empty
  }
  
  return result;
}