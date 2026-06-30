// FUNC_NAME: String::hashLower
int String::hashLower(byte *str)
{
  int hash = 0;
  byte c;

  if (str != (byte *)0x0) {
    c = *str;
    while (c != 0) {
      // Convert uppercase ASCII (A-Z) to lowercase
      if (c - 0x41 < 0x1a) {
        c = c + 0x20;
      }
      // Hash: hash = hash * 65599 + character
      hash = hash * 0x1003f + c;
      c = *str;
      str = str + 1;
    }
  }
  return hash;
}