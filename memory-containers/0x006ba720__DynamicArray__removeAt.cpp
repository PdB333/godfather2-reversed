// FUNC_NAME: DynamicArray::removeAt
void __thiscall DynamicArray::removeAt(int *this, uint index)
{
  int count = this[1]; // +0x04: number of elements
  int *data = (int *)this[0]; // +0x00: pointer to element array

  if (index < count - 1)
  {
    do {
      data[index] = data[index + 1];
      index++;
    } while (index < count - 1);
  }

  this[1] = count - 1; // decrement element count
}