// FUNC_NAME: GrowableArray::addEntry
int __fastcall GrowableArray::addEntry(int *this)
{
  int capacity = this[2]; // +0x08: capacity
  int size = this[1];     // +0x04: current size
  
  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity = capacity * 2;
    }
    GrowableArray::resize(capacity); // FUN_009097e0 - reallocate array
  }
  
  // Clear the new entry (8 bytes per element)
  int *newEntry = (int *)(this[0] + size * 8); // +0x00: data pointer
  if (newEntry != (int *)0x0) {
    newEntry[0] = 0;
    newEntry[1] = 0;
  }
  
  this[1] = size + 1; // increment size
  return this[0] + size * 8; // return pointer to new entry
}