// FUNC_NAME: String::assign
int * __thiscall String::assign(int *this, char *source)
{
  char cChar;
  char *pcSrcIter;
  int iLength;
  void *pBuffer;
  
  if ((source != (char *)0x0) && (*source != '\0')) {
    // Calculate string length
    pcSrcIter = source;
    do {
      cChar = *pcSrcIter;
      pcSrcIter = pcSrcIter + 1;
    } while (cChar != '\0');
    iLength = (int)pcSrcIter - (int)(source + 1);
    
    // Store length and capacity
    this[1] = iLength;    // +0x04: string length
    this[2] = iLength;    // +0x08: buffer capacity
    
    // Allocate new buffer
    pBuffer = (void *)FUN_009c8e50(iLength + 1);
    this[0] = (int)pBuffer;  // +0x00: buffer pointer
    
    // Copy string content
    _memcpy(pBuffer, source, this[1]);
    *(undefined1 *)(this[0] + this[1]) = 0;  // Null-terminate
    
    // Set destructor function pointer (for custom allocator)
    this[3] = (int)thunk_FUN_009c8eb0;  // +0x0C: deallocation function
    
    return this;
  }
  
  // Empty string: zero out all fields
  this[0] = 0;
  this[2] = 0;
  this[1] = 0;
  return this;
}