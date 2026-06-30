// FUNC_NAME: strncpy_safe
void __fastcall strncpy_safe(char *dest, const char *src, int maxLen)
{
  // Copy up to maxLen-1 characters from src to dest, null-terminating the result.
  // This is a bounded string copy that ensures no buffer overflow.
  if (maxLen != 0) {
    do {
      if (*src == '\0') break;
      *dest = *src;
      dest++;
      src++;
      maxLen--;
    } while (maxLen != 0);
  }
  *dest = '\0';
}