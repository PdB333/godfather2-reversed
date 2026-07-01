// FUNC_NAME: GrowingArray::addElement
int* __fastcall GrowingArray::addElement(GrowingArray* thisPtr)
{
  int capacity = thisPtr->capacity; // +0x08
  if (thisPtr->size == capacity) {   // +0x04
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity *= 2;
    }
    FUN_00893840(capacity);  // likely realloc/grow (takes new capacity)
  }
  int size = thisPtr->size++;        // +0x04, increment after use
  return (int*)((char*)thisPtr->data + size * 8); // +0x00, element size 8 bytes
}