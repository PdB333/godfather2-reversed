// FUNC_NAME: EARSString::findChar
char * __thiscall EARSString::findChar(char ch, char *searchStr)
{
  char *found;

  found = (char *)0x0;
  if (searchStr != (char *)0x0) {
    found = _strchr(searchStr,(int)ch);
    return found;
  }
  if (this->m_string != (char *)0x0) {
    found = _strchr(this->m_string,(int)ch);
  }
  return found;
}