// FUNC_NAME: skipWhitespaceAndParseSign
char * skipWhitespaceAndParseSign(char *inputString, char *signOut)
{
  char currentChar;
  
  // Skip whitespace characters: space, newline, tab, carriage return, form feed, vertical tab
  for (; (((currentChar = *inputString, currentChar == ' ' || (currentChar == '\n')) || (currentChar == '\t')) ||
         (((currentChar == '\r' || (currentChar == '\f')) || (currentChar == '\v')))); inputString = inputString + 1) {
  }
  
  // Check for sign character
  if (*inputString != '+') {
    if (*inputString != '-') {
      // No sign found, output 0 (no sign)
      *signOut = 0;
      return inputString;
    }
    // Negative sign found, output '-' (0x2d)
    *signOut = 0x2d;
    return inputString + 1;
  }
  
  // Positive sign found, output '+' (0x2b)
  *signOut = 0x2b;
  return inputString + 1;
}