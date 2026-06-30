// FUNC_NAME: ArrayContainer::findAndRemove
// Function address: 0x005c0c50
// This method searches backwards through an internal array (24-byte stride?) for an entry matching given keys,
// then performs an operation via an external function. Sets a dirty flag if the matching element is at a specific index.
// Struct offsets:
// +0x00: pointer to array of 12-byte entries (each entry: first int key2, second int key1)
// +0x04: current number of entries (size)
// +0x10: maximum capacity or threshold index
// +0x14: flag byte (1 = dirty / modified)

void __thiscall ArrayContainer::findAndRemove(int *this, int key1, int key2)
{
  int currentSize = this[1];           // +0x04
  int threshold = this[4];             // +0x10
  int index = currentSize - 1;         // start from last element

  // Only iterate if we are past the threshold
  if (threshold <= index) {
    int arrayBase = *this;             // +0x00, pointer to array of 12-byte entries
    int byteOffset = index * 12;       // each entry is 12 bytes
    do {
      // Check if both keys match: first int = key2, second int = key1
      if (*(int *)(arrayBase + byteOffset) == key2 &&
          *(int *)(arrayBase + byteOffset + 4) == key1) {
        // Call external processing function (e.g., unlink, remove, or update)
        FUN_005c2a70();
        if (index == threshold) {
          // If the matching entry is at the threshold index, mark modification
          *(unsigned char *)(this + 5) = 1;   // +0x14 flag byte
        }
      }
      index--;
      byteOffset -= 12;
    } while (threshold <= index);  // continue while index >= threshold
  }
}