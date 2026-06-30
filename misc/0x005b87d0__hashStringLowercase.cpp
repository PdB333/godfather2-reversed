// FUNC_NAME: hashStringLowercase
int __fastcall hashStringLowercase(undefined4 this, byte* str)
{
  int hash = 0;
  byte c;
  
  do {
    c = *str;
    str++;
    if (c - 0x41 < 0x1a) {  // 'A' to 'Z' -> convert to lowercase
      c = c + 0x20;         // ASCII lowercase conversion
    }
    hash = hash * 0x21 + c; // hash = hash * 33 + character
  } while (c != 0);         // stop at null terminator
  
  return hash;
}