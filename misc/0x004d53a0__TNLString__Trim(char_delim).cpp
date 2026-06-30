// FUNC_NAME: TNLString::Trim(char delim)
void __thiscall TNLString::Trim(int *this, char delim)
{
  char cVar1;
  char *dst;
  char *src;
  char *pcVar2;
  uint size;
  
  if (this[1] != 0) {
    dst = (char *)*this;
    cVar1 = *dst;
    src = dst;
    while (cVar1 == delim) {
      src = src + 1;
      cVar1 = *src;
    }
    cVar1 = (dst + this[1])[-1];
    pcVar2 = dst + this[1];
    while (cVar1 == delim) {
      cVar1 = pcVar2[-2];
      pcVar2 = pcVar2 + -1;
    }
    size = (int)pcVar2 - (int)src;
    if (size < (uint)this[1]) {
      if (pcVar2 < src) {
        FUN_00401060(); // likely memory underflow error
        return;
      }
      this[1] = size;
      _memcpy(dst, src, size);
      *(undefined1 *)(*this + this[1]) = 0; // null-terminate
    }
  }
  return;
}