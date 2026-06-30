// FUNC_NAME: DynamicArray::clear
void DynamicArray::clear(void)
{
  // this = ESI
  // Structure layout:
  // +0x00: int capacity (number of elements allocated)
  // +0x04: int size (number of elements used)
  // +0x08: int elementSize (size of each element)
  // +0x0C: void* data (pointer to allocated array)
  
  if (this->data != (void *)0x0) {
    // Zero out the allocated memory (capacity * elementSize bytes)
    _memset(this->data,0,this->capacity * 4);
    // Free the allocated memory
    _free(this->data);
    // Reset all fields
    this->data = 0;
    this->capacity = 0;
    this->size = 0;
    this->elementSize = 0;
  }
  return;
}