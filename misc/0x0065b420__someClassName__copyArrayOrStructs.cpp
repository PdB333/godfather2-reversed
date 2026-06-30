// FUNC_NAME: someClassName::copyArrayOrStructs
void __fastcall someClassName::copyArrayOrStructs(int count, int source)
{
  int i;
  undefined8 *dest;
  
  if (count != 0) {
    i = 0;
    do {
      dest = (undefined8 *)(DAT_01223360 + i);
      if (dest != (undefined8 *)0x0) {
        *dest = *(undefined8 *)(i + source);                // copy 8 bytes
        *(undefined4 *)(dest + 1) = *(undefined4 *)(i + 8 + source); // copy next 4 bytes (total 12 bytes)
      }
      i = i + 0xc;                                           // each element is 0xC (12) bytes
      count = count + -1;
    } while (count != 0);
  }
  return;
}