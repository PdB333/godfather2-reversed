// FUNC_NAME: DynamicArray<int>::copyFrom
int * __thiscall DynamicArray<int>::copyFrom(int *this, int *other)
{
  int capacity;
  int *newBuffer;
  uint i;

  capacity = other[2];
  this[2] = capacity;
  this[1] = other[1];
  if (capacity == 0) {
    this[0] = 0;
  }
  else {
    newBuffer = (int *)FUN_009c8e80(capacity * 4); // likely malloc or operator new[]
    i = 0;
    this[0] = (int)newBuffer;
    if (this[1] != 0) {
      do {
        newBuffer[i] = *(int *)(i * 4 + (int)other);
        i = i + 1;
      } while (i < (uint)this[1]);
      return this;
    }
  }
  return this;
}