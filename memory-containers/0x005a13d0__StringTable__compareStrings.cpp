// FUNC_NAME: StringTable::compareStrings
void __fastcall StringTable::compareStrings(int *this, int *otherString)
{
  int i;
  char *thisChar;
  char *otherChar;

  i = 0;
  if (*this == *otherString) { // Compare lengths first
    do {
      if (*this <= i) { // Reached end of string without mismatch
        return;
      }
      thisChar = (char *)(i + this[2]); // +0x08: string data pointer
      otherChar = (char *)(i + otherString[2]); // +0x08: string data pointer
      i = i + 1;
    } while (*thisChar == *otherChar);
  }
  return;
}