// FUNC_NAME: DynamicArray::push
void DynamicArray::push(int32_t value) {
  // this is in EAX
  int32_t* data = *(int32_t**)this;      // +0x00: pointer to int array
  int32_t size = *(int32_t*)((char*)this + 4);   // +0x04: current size
  int32_t capacity = *(int32_t*)((char*)this + 8); // +0x08: allocated capacity

  if (size == capacity) {
    int32_t newCapacity = (capacity == 0) ? 1 : (capacity * 2);
    resize(newCapacity); // FUN_005e6ff0
  }

  // Store value and increment size
  int32_t* slot = data + size;
  *(int32_t*)((char*)this + 4) = size + 1;
  if (slot != nullptr) {
    *slot = value;
  }
}