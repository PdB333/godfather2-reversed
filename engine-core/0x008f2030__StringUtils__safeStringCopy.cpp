// FUNC_NAME: StringUtils::safeStringCopy
void __thiscall safeStringCopy(char *dest, char *src)
{
  // Copy up to 63 characters (0x3f) and null-terminate
  _strncpy(dest, src, 0x3f);
  dest[0x3f] = '\0';
  return;
}