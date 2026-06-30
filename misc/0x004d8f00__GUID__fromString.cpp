// FUNC_NAME: GUID::fromString
void __thiscall GUID::fromString(undefined4 *this, char *str)
{
  char isValid;
  int i;
  
  isValid = FUN_004d9400(str); // likely GUID::isValidFormat or similar
  i = 9;
  if (isValid == '\0') {
    str = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}"; // fallback invalid GUID
  }
  // Copy 36 bytes (9 * 4) from string to GUID structure (16 bytes total? Actually 36 bytes of string)
  // This loop copies 9 dwords (36 bytes) from the string representation
  for (; i != 0; i = i + -1) {
    *this = *(undefined4 *)str;
    str = str + 4;
    this = this + 1;
  }
  // Copy remaining 2 bytes + 1 byte = 3 bytes (total 39 bytes? Actually GUID string is 36 chars + null = 37)
  *(undefined2 *)this = *(undefined2 *)str;
  *(char *)((int)this + 2) = str[2];
  return;
}