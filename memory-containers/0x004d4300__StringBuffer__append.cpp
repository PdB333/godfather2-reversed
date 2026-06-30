// FUNC_NAME: StringBuffer::append
// Function address: 0x004d4300
// - Appends a C string to a dynamically allocated buffer, with auto-resize.
// Fields of StringBuffer (offsets from this):
//   +0x00: char* buffer
//   +0x04: int size        // current length (excluding null)
//   +0x08: int capacity    // allocated size (including null)
//   +0x0C: void (*deallocator)(void*)
StringBuffer* __thiscall StringBuffer::append(StringBuffer* this, const char* str)
{
  uint newLen;
  char c;
  const char* p;
  size_t strLen;
  void* newBuffer;

  if (str == nullptr || *str == '\0') {
    return this;
  }

  // Calculate length of str (excluding null terminator)
  p = str;
  do {
    c = *p;
    p++;
  } while (c != '\0');
  strLen = (size_t)(p - (str + 1));

  if (this->capacity != 0) {
    newLen = this->size + strLen;
    if (newLen < (uint)this->capacity) {
      // Enough capacity: just copy
      memcpy((void*)(this->buffer + this->size), str, strLen);
    }
    else {
      // Need larger capacity: allocate new buffer
      newBuffer = (void*)FUN_009c8e50(newLen + 1);  // memory allocation
      memcpy(newBuffer, this->buffer, this->size);
      memcpy((void*)(this->size + (int)newBuffer), str, strLen);
      if (this->buffer != nullptr) {
        // Call deallocator function stored at +0x0C
        ((void (*)(void*))this->deallocator)(this->buffer);
      }
      this->capacity = newLen;
      this->buffer = (char*)newBuffer;
      this->deallocator = (void (*)(void*))0x009c8eb0; // thunk_FUN_009c8eb0, deallocation
    }
    this->size += strLen;
    *(this->buffer + this->size) = '\0';
    return this;
  }

  // First allocation: capacity is zero, allocate exactly for this string
  newBuffer = (void*)FUN_009c8e50(strLen + 1);
  this->buffer = (char*)newBuffer;
  this->deallocator = (void (*)(void*))0x009c8eb0;
  this->capacity = strLen;
  // Copy str including null terminator
  p = str;
  do {
    c = *p;
    *((char*)newBuffer) = c;
    newBuffer = (char*)newBuffer + 1;
    p++;
  } while (c != '\0');
  this->size = strLen;
  return this;
}