// FUNC_NAME: EARS::Array::reserve

void __thiscall EARS::Array::reserve(unsigned int newCapacity)
{
  // If current capacity is insufficient, reallocate
  if (this->capacity < newCapacity) {
    // Allocate new buffer: newCapacity * elementSize (0x10 bytes)
    char *newBuffer = (char *)operator new(newCapacity << 4);
    int srcOffset = 0;
    unsigned int copiedCount = 0;

    if (this->buffer != (int *)0x0) {
      char *src = (char *)this->buffer;
      char *dst = newBuffer;

      if (this->size != 0) {
        do {
          // Copy first DWORD of element directly
          *(unsigned int *)dst = *(unsigned int *)src;

          // Handle second field: copy constructor / move + release old
          // (FUN_00792150 likely performs a deep copy of the resource
          //  pointed to by the second DWORD, storing it into the new element)
          EARS::Array::copySecondField(src + 4);

          // Free the original resource (old element's second field)
          if (*(unsigned int *)(src + 4) != 0) {
            operator delete(*(void **)(src + 4));
          }

          copiedCount++;
          src += 0x10;   // +16 bytes
          dst += 0x10;
          srcOffset += 0x10;
        } while (copiedCount < this->size);
      }

      // Release old buffer
      operator delete(this->buffer);
    }

    this->buffer = (int *)newBuffer;
    this->capacity = newCapacity;
  }
}