// FUNC_NAME: EntityDataManager::guidToReprId
int EntityDataManager::guidToReprId(void* thisPtr)
{
  char buffer[28]; // stack buffer for hash conversion
  char* str;
  char c;
  int result;

  if ((*(int*)thisPtr == 0 && *(int*)(thisPtr + 4) == 0) && (*(int*)(thisPtr + 8) == 0 && *(int*)(thisPtr + 12) == 0)) {
    return 0; // null GUID
  }

  // Convert GUID to hex string representation
  FUN_004eaec0(thisPtr, buffer);

  // Find end of string
  str = buffer;
  do {
    c = *str;
    str = str + 1;
  } while (c != '\0');

  // Call hash function on the string (length = str - buffer - 1)
  FUN_00ab8560(0, buffer, (int)str - (int)(buffer + 1));

  result = FUN_00616720(); // get hash result as ID
  return result;
}