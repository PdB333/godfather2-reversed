// FUNC_NAME: ObjectArrayManager::releaseAll
void __thiscall ObjectArrayManager::releaseAll(ObjectArrayManager *this)
{
  int *arrayEnd;
  int *current;
  int element;
  int *refCountPtr;
  
  current = *(int **)(this + 0x208); // pointer to array of pointers (elements)
  arrayEnd = current + *(int *)(this + 0x20c); // count of elements
  if (current != arrayEnd) {
    do {
      element = *current; // value of element (pointer to some object)
      if (element != 0) {
        refCountPtr = *(int **)(element + 8); // pointer to a reference-counted structure? Actually offset 8 contains a pointer
        // Decrement reference count (first integer of that structure)
        (*refCountPtr)--;
        if (*refCountPtr == 0) {
          // Call virtual destructor on the structure: vtable at offset 0x10C (0x43 * 4), function 0x18 from vtable
          (**(void (__thiscall ***)(void *, int))(*(int *)(refCountPtr[0x43]) + 0x18))(refCountPtr);
        }
        // Release the element object
        FUN_009c8eb0(element);
      }
      current++;
    } while (current != (int *)(*(int *)(this + 0x208) + *(int *)(this + 0x20c) * 4));
  }
  // Clear the array
  *(int *)(this + 0x20c) = 0; // count
  FUN_009c8f10(*(int *)(this + 0x208)); // free the array buffer
  *(int *)(this + 0x208) = 0; // array pointer
  *(int *)(this + 0x210) = 0; // capacity
  return;
}