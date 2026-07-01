// FUNC_NAME: DynamicArray::destroy
void __thiscall DynamicArray::destroy(int *this)
{
  int count;
  int i;
  int elementPtr;

  count = this[1] + -1;
  if (count >= 0) {
    i = count * 0xc;
    do {
      elementPtr = *this + i;
      if (*(int *)elementPtr != 0) {
        // Destructor for each element (0xC bytes each)
        SomeClass::destructor(elementPtr);
      }
      count = count + -1;
      i = i + -0xc;
    } while (count >= 0);
  }
  if (*this != 0) {
    // Free the underlying array memory
    operatorDelete((void *)*this);
  }
  return;
}