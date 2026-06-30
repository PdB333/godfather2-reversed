// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
  // +0x00: pointer to data (likely)
  // +0x04: current capacity (number of elements)
  // +0x08: pointer to allocated memory (data array)
  
  if (*(uint *)(this + 4) < newCapacity) {
    int alignedCapacity = newCapacity + (0x10 - (newCapacity & 0xf));
    void* newData = malloc(alignedCapacity * 4);
    void* oldData = *(void**)(this + 8);
    *(void**)(this + 8) = newData;
    // Copy old data to new buffer (FUN_006600e0 likely memcpy or element copy)
    FUN_006600e0(oldData);
    *(void**)(this + 8) = oldData;
    free(oldData);
    *(void**)(this + 8) = newData;
    *(int*)(this + 4) = alignedCapacity;
  }
}