// FUNC_NAME: Array::copyFrom
void Array::copyFrom(Array* src)
{
  // Member fields at offsets:
  // +0x00: pointer to data
  // +0x04: count of elements
  // +0x08: capacity

  int capacity = src->capacity;
  this->capacity = capacity;
  this->count = src->count;

  if (capacity == 0) {
    this->data = 0;
    return;
  }

  // Allocate memory for capacity elements (each 0x14 = 20 bytes)
  this->data = (ElementType*)allocateMemory(capacity * sizeof(ElementType));
  int idx = 0;
  if (this->count != 0) {
    do {
      ElementType* dst = &this->data[idx];
      ElementType* srcElem = &src->data[idx];
      *dst = *srcElem; // shallow copy of first two fields (8 bytes)
      // Deep copy of the third field (offset 8, size 12? but we call copy ctor)
      copyElement(&srcElem->field3); // assuming field3 at offset 8
      idx++;
    } while (idx < this->count);
  }
}

// Helper function: memory allocator
void* allocateMemory(size_t size);

// Helper function: copy constructor for element type (size 0x14)
void copyElement(void* dest);