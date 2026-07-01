// FUNC_NAME: parseIntegerFromString
char * __thiscall parseIntegerFromString(char *str)
{
  char *endPtr;
  long value;
  char *digitStart;
  char *allocatedStr;
  long *outValue;
  
  // Skip leading digits
  for (digitStart = str; (int)*digitStart - 0x30U < 10; digitStart = digitStart + 1) {
  }
  
  if (str < digitStart) {
    // Allocate and copy the digit substring
    FUN_004d3c40(str, (int)digitStart - (int)str); // likely strndup or similar
    allocatedStr = (char *)0x0; // return value from FUN_004d3c40
    if (allocatedStr == (char *)0x0) {
      allocatedStr = &DAT_0120546e; // empty string fallback
    }
    value = _atol(allocatedStr);
    *outValue = value;
    if (allocatedStr != (char *)0x0) {
      // Free the allocated string
      (*(code *)0x0)(allocatedStr); // likely operator delete or free
    }
  }
  return digitStart; // return pointer past the parsed digits
}