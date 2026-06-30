// FUNC_NAME: String::assignFromCString
int * __thiscall String::assignFromCString(int *this, undefined4 *sourceString)
{
  int length;
  void *newBuffer;
  
  length = sourceString[1]; // +0x04: cached length of source string
  if (length != 0) {
    this[1] = length; // +0x04: set buffer length
    this[2] = length; // +0x08: set string length
    newBuffer = (void *)FUN_009c8e50(length + 1); // allocate memory for string + null terminator
    *this = (int)newBuffer; // +0x00: set buffer pointer
    _memcpy(newBuffer,(void *)*sourceString,this[1]); // copy string data
    *(undefined1 *)(*this + this[1]) = 0; // null-terminate
    this[3] = (int)thunk_FUN_009c8eb0; // +0x0C: set deallocation function pointer
    return this;
  }
  *this = 0; // +0x00: null buffer
  this[2] = 0; // +0x08: zero length
  this[1] = 0; // +0x04: zero buffer length
  return this;
}