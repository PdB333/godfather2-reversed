//FUNC_NAME: ObjectArray::clearAndDestroy

void __thiscall ObjectArray::clearAndDestroy(ObjectArray *this)
{
  int **arrayPtr; // pointer to array of pointers
  int *element;   // current element pointer
  int **endPtr;   // end of array

  // Set flag at +0x10 to 0 (e.g., "initialized" or "owns")
  *(byte *)(this + 0x10) = 0;

  arrayPtr = *(int ***)(this + 4); // +0x4: pointer to array of pointers
  if (arrayPtr != (int **)((int)arrayPtr + *(int *)(this + 8) * 4)) {
    do {
      element = *arrayPtr;
      if (element != (int *)0x0) {
        // Call first virtual function (likely release/destroy) with argument 1
        (**(code **)*element)(1);
      }
      element = (int *)*arrayPtr;
      if (element != (int *)0x0) {
        // If element has a sub-pointer at offset 0, free it
        if (*element != 0) {
          FUN_004daf90(element); // custom deallocator
        }
        FUN_009c8eb0(element); // standard free
      }
      arrayPtr++;
    } while (arrayPtr != (int **)(*(int *)(this + 4) + *(int *)(this + 8) * 4));
  }

  // Reset count to 0
  *(int *)(this + 8) = 0; // +0x8: count

  // Free the array itself
  FUN_009c8f10(*(int *)(this + 4)); // free array memory

  // Clear pointer and capacity
  *(int *)(this + 4) = 0;  // +0x4: array pointer
  *(int *)(this + 0xc) = 0; // +0xc: capacity or similar
}