// FUNC_NAME: UUID::fromString

void __thiscall UUID::fromString(undefined4 *this, const char *uuidString)
{
  char isValid;
  int i;

  // Validate the input string; if invalid, replace with a default "bad" UUID
  isValid = FUN_004d9400(uuidString);
  if (isValid == '\0') {
    uuidString = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
  }

  // Copy the 39-byte UUID string (including null terminator) into the destination buffer
  // This is an unrolled copy: 9 DWORDs (36 bytes) + 1 WORD (2 bytes) + 1 byte = 39 bytes
  for (i = 9; i != 0; i = i + -1) {
    *this = *(undefined4 *)uuidString;
    uuidString = uuidString + 4;
    this = this + 1;
  }
  *(undefined2 *)this = *(undefined2 *)uuidString;   // copy remaining 2 bytes
  *(char *)((int)this + 2) = uuidString[2];          // copy final byte
  return;
}