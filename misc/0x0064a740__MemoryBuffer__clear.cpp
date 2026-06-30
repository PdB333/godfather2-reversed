// FUNC_NAME: MemoryBuffer::clear
void MemoryBuffer::clear(void)
{
  uint i;
  
  if (this->buffer != 0) {
    i = 0;
    if (this->size != 0) {
      do {
        *(undefined4 *)(this->buffer + i * 4) = 0;
        i = i + 1;
      } while (i < (uint)this->size);
    }
    if (this->deallocator != (code *)0x0) {
      (*(code *)this->deallocator)(this->allocatorData, this->buffer, this->size * 4, this->deallocatorArg);
    }
    this->buffer = 0;
    this->size = 0;
    this->capacity = 0;
  }
  return;
}