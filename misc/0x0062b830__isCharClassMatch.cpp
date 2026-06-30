// FUNC_NAME: isCharClassMatch
uint isCharClassMatch(int charClass, int testChar)
{
  int lowerCharClass;
  uint result;
  
  lowerCharClass = _tolower(charClass);
  switch(lowerCharClass) {
  case 'a':
    result = _isalpha(testChar);
    break;
  default:
    return (uint)(charClass == testChar);
  case 'c':
    result = _iscntrl(testChar);
    break;
  case 'd':
    result = _isdigit(testChar);
    break;
  case 'l':
    result = _islower(testChar);
    break;
  case 'p':
    result = _ispunct(testChar);
    break;
  case 's':
    result = _isspace(testChar);
    break;
  case 'u':
    result = _isupper(testChar);
    break;
  case 'w':
    result = _isalnum(testChar);
    break;
  case 'x':
    result = _isxdigit(testChar);
    break;
  case 'z':
    result = (uint)(testChar == 0);
  }
  
  // If the character class specifier is lowercase, return the result directly
  // If uppercase, invert the result (negation)
  if (_islower(charClass) != 0) {
    return result;
  }
  return (uint)(result == 0);
}