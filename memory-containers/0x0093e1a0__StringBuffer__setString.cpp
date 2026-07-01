// FUNC_NAME: StringBuffer::setString
undefined4 * __thiscall StringBuffer::setString(undefined4 *this, char *sourceString, undefined4 param_3, undefined2 param_4, int param_5)
{
  char cVar1;
  char *pcVar2;
  void *_Dst;
  
  // +0x10: unknown field
  *(undefined2 *)(this + 4) = param_4;
  // +0x00: buffer pointer (initially null)
  *this = 0;
  // +0x04: buffer length
  this[1] = 0;
  // +0x08: initial capacity (5)
  this[2] = 5;
  // +0x12: unknown field
  *(undefined2 *)((int)this + 0x12) = 0;
  // +0x14: max size (15000)
  *(undefined2 *)(this + 5) = 15000;
  // +0x18: unknown
  this[6] = 0;
  // +0x1c: unknown
  this[7] = 0;
  
  // Calculate string length
  pcVar2 = sourceString;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  
  // Allocate memory for string copy (including null terminator)
  _Dst = (void *)FUN_009c8e80(pcVar2 + (1 - (int)(sourceString + 1)));
  // +0x20: pointer to allocated string copy
  this[8] = _Dst;
  _memcpy(_Dst, sourceString, (size_t)(pcVar2 + (1 - (int)(sourceString + 1))));
  
  // +0x24: some parameter
  this[9] = param_3;
  
  if (param_5 != 0) {
    // +0x0c: offset from some global base (DAT_01205224)
    this[3] = param_5 + DAT_01205224;
    return this;
  }
  this[3] = 0;
  return this;
}