// FUNC_NAME: ObjectArray::addObject
void __thiscall ObjectArray::addObject(int this, int object)
{
  int* piVar1;
  int count;
  int capacity;
  int newCapacity;

  if (object != 0) {
    count = *(int *)(this + 0x44);
    capacity = *(int *)(this + 0x48);
    if (count == capacity) {
      if (capacity == 0) {
        newCapacity = 1;
      }
      else {
        newCapacity = capacity * 2;
      }
      FUN_00456b10(newCapacity); // likely reallocate internal array
    }
    // Calculate pointer to new slot (each slot is 8 bytes)
    piVar1 = (int *)(*(int *)(this + 0x40) + count * 8);
    *(int *)(this + 0x44) = count + 1;
    *piVar1 = object; // store object pointer
    // Store hash or identifier associated with object
    piVar1[1] = FUN_004dafd0(object);
  }
}