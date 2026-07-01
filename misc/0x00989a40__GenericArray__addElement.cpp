// FUNC_NAME: GenericArray::addElement
int __fastcall GenericArray::addElement(GenericArray *this)
{
  int capacity;
  int *data;
  int newCapacity;

  capacity = this->capacity; // +0x08
  if (this->size == capacity) { // +0x04 == +0x08
    if (capacity == 0) {
      newCapacity = 1;
    } else {
      newCapacity = capacity * 2;
    }
    FUN_00407880(newCapacity); // Reallocate internal buffer to newCapacity elements (each 16 bytes)
  }
  data = this->data; // +0x00
  int index = this->size; // +0x04
  // Zero out the new element (assumed to be 16 bytes)
  if (data != nullptr) {
    int *newSlot = &data[index * 4]; // Each element is 4 ints (16 bytes)
    newSlot[0] = 0;
    newSlot[1] = 0;
    newSlot[2] = 0;
    newSlot[3] = 0;
  }
  this->size = index + 1;
  return (int)(data + index * 4); // Return pointer to the new element (as raw address)
}