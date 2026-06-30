// FUNC_NAME: FixedSizeArray::removeLastElement
void __thiscall FixedSizeArray::removeLastElement(int *thisPtr, int elementIndex)
{
  // thisPtr[0] = pointer to allocated array data
  // thisPtr[1] = current number of elements (size)
  // param2 = index of element to remove
  
  if (elementIndex != thisPtr[1] + -1) {
    // If not removing the last element, copy the last element to the removed position
    *(undefined4 *)(*thisPtr + elementIndex * 4) = *(undefined4 *)(*thisPtr + -4 + thisPtr[1] * 4);
  }
  // Decrement the element count
  thisPtr[1] = thisPtr[1] + -1;
}