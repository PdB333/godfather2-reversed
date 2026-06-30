// FUNC_NAME: StringSearchHelper::findSubstring
void __thiscall StringSearchHelper::findSubstring(undefined4 *this, char *substring, char *searchIn)
{
  if ((substring != (char *)0x0) && (*substring != '\0')) {
    if (searchIn != (char *)0x0) {
      _strstr(searchIn,substring);
      return;
    }
    if ((char *)*this != (char *)0x0) {
      _strstr((char *)*this,substring);
    }
  }
  return;
}