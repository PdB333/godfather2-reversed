// FUNC_NAME: StringCompare::compareCaseInsensitive
int __thiscall StringCompare::compareCaseInsensitive(StringData *this, StringData *other)
{
  char *otherStr;
  char *thisStr;
  int result;
  
  // If this string has no data, return whether other has data
  if (this->data == 0) {
    return (int)(other->data != 0);
  }
  
  // If other string has data, compare them
  if (other->data != 0) {
    otherStr = (char *)other->str;  // +0x00: string pointer
    thisStr = (char *)this->str;    // +0x00: string pointer
    
    // If both pointers are valid, do case-insensitive comparison
    if ((thisStr != (char *)0x0) && (otherStr != (char *)0x0)) {
      result = __stricmp(thisStr, otherStr);
      return result;
    }
    
    // If one pointer is null, compare pointer values
    if (thisStr <= otherStr) {
      return (int)(thisStr < otherStr);
    }
  }
  
  // Default: this string is greater
  return 0xffffffff;
}