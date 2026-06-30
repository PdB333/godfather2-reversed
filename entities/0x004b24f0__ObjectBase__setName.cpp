// FUNC_NAME: ObjectBase::setName
void __thiscall ObjectBase::setName(int thisPtr, char* name)
{
  char* newStr;
  char* tempPtr;
  char* src;
  int zero1; // unused, part of tempString struct
  int zero2; // unused, part of tempString struct
  void (*deleter)(char*); // deallocation function pointer

  if ((name == (char*)0x0) || (*name == '\0')) {
    // Clear the name buffer (offset 0x64c, size 0x100)
    _memset((void*)(thisPtr + 0x64c), 0, 0x100);
  }
  else {
    char* dest = (char*)(thisPtr + 0x64c);
    // Copy input into internal buffer first (safe because size matches)
    _strncpy(dest, name, 0x100);

    // Initialize a temporary custom string struct (likely EA::FixedString or similar)
    newStr = (char*)0x0;
    zero1 = 0;
    zero2 = 0;
    deleter = (void (*)(char*))0x0;

    // Assign internal buffer content to temporary string (may normalize or resolve path)
    // FUN_00401a20 is a string assignment that may allocate or update internal pointer
    StringAssign(&newStr, dest); // signature: void StringAssign(char** outStr, const char* src)

    tempPtr = newStr;
    src = newStr;
    if (newStr == (char*)0x0) {
      // If allocation failed, fall back to a default (DAT_0120546e is probably an empty string)
      src = (char*)&DAT_0120546e;
    }

    // Copy the normalized/processed string back into the internal buffer
    _strncpy(dest, src, 0x100);

    // If the temporary string allocated heap memory, free it using the deleter
    if (tempPtr != (char*)0x0) {
      (*deleter)(tempPtr);
    }
  }
}