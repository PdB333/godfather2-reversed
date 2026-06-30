// FUNC_NAME: MemStream::readStringIntoBuffer
undefined4 * __thiscall MemStream::readStringIntoBuffer(int *this,undefined4 *outParam,char *src)
{
  char *pcVar1;
  char cVar2;
  int len;
  int strLen;
  int remaining;
  int field_0;
  
  remaining = this[1]; // +0x04 : remaining data size in stream
  if (remaining != 0) {
    pcVar1 = src + 1;
    do {
      cVar2 = *src;
      src = src + 1;
    } while (cVar2 != '\0');
    field_0 = *this; // +0x00 : current read position in buffer
    len = FUN_004d4e20(field_0); // some length or position check
    if (len != 0) {
      do {
        strLen = len;
        len = FUN_004d4e20(src + (strLen - (int)pcVar1));
      } while (len != 0);
      if ((strLen != 0) && (src[strLen - (int)pcVar1] != '\0')) {
        outParam[3] = 0;
        FUN_004d3c40(src + (strLen - (int)pcVar1), // string to copy
                     (field_0 - (int)(src + (strLen - (int)pcVar1))) + remaining); // max bytes
        return outParam;
      }
    }
  }
  *outParam = 0;
  outParam[1] = 0;
  outParam[2] = 0;
  outParam[3] = 0;
  return outParam;
}