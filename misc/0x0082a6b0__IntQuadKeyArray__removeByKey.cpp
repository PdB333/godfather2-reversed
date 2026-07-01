// FUNC_NAME: IntQuadKeyArray::removeByKey
int __thiscall IntQuadKeyArray::removeByKey(int *key) {
  uint count = *(uint *)(this + 0x0c);          // number of elements in array
  uint index = 0;
  
  if (count != 0) {
    int **arrayPtr = *(int ***)(this + 0x08);   // pointer to array of object pointers
    do {
      int *object = arrayPtr[index];            // pointer to the current object
      
      // Compare four ints from the object at offsets 0x1c, 0x20, 0x24, 0x28 with the key
      if ((object[0x07] == key[0]) &&           // +0x1c = key component 0
          (object[0x08] == key[1]) &&           // +0x20 = key component 1
          (object[0x09] == key[2]) &&           // +0x24 = key component 2
          (object[0x0a] == key[3])) {           // +0x28 = key component 3
        
        // Remove the element: if not the last one, shift all following elements left
        if (index < count - 1) {
          do {
            *(int **)(this + 0x08)[index] = *(int **)(this + 0x08)[index + 1];
            index++;
          } while (index < count - 1);
        }
        
        // Decrease the element count and return the removed object pointer
        *(int *)(this + 0x0c) = count - 1;
        return object;
      }
      
      index++;
    } while (index < count);
  }
  
  return 0;
}