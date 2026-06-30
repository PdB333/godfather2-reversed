// FUNC_NAME: SomeClass::clearArray
void clearArray(void)
{
  undefined4 *this;
  
  this[2] = 0;          // +0x08: elementCount = 0
  *this = 0;            // +0x00: arrayPtr = null or some flag = 0
  _memset((void *)this[3],0,this[1] * 4);  // +0x0C: zero out allocated buffer (size = this[1] * 4 bytes)
  return;
}