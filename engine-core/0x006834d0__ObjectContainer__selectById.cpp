// FUNC_NAME: ObjectContainer::selectById
void __thiscall ObjectContainer::selectById(int this, int id)
{
  uint index;
  int *keyPtr;
  int *valuePtr;

  valuePtr = (int *)0x0;
  if (*(int *)(this + 0x88) != 0) {
    keyPtr = (int *)(this + 8);
    do {
      if (*keyPtr == id) {
        // Found matching key; retrieve corresponding value pointer
        // Each entry: key at base+0, value at base+4, stride 8 bytes
        valuePtr = *(int **)(this + 0xc + index * 8);
        break;
      }
      index = index + 1;
      keyPtr = keyPtr + 2;
    } while (index < *(uint *)(this + 0x88));
  }
  // Set the current selected object pointer
  *(int **)(this + 4) = valuePtr;
  if (valuePtr != (int *)0x0) {
    // Call the second virtual function on the selected object (vtable+4)
    // Typically an initialization or activation routine
    (**(code **)(*valuePtr + 4))(0);
  }
  return;
}