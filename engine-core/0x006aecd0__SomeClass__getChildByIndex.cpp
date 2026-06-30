// FUNC_NAME: SomeClass::getChildByIndex
int __thiscall SomeClass::getChildByIndex(int thisPtr, int index)
{
  int childPtr;
  
  // Access child pointer array at offset +0x1ac, each entry is 8 bytes
  // The array stores pointers to child objects
  childPtr = *(int *)(thisPtr + 0x1ac + index * 8);
  if (childPtr != 0) {
    // Return pointer to the beginning of the child object (subtract 0x48 to get base)
    return childPtr - 0x48;
  }
  return 0;
}