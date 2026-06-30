// FUNC_NAME: SomeContainer::findByKey
undefined4 __thiscall SomeContainer::findByKey(int this, undefined4 key)
{
  char cVar1;
  undefined4 result;
  uint index;
  
  result = 0;
  index = 0;
  // Check if there are any elements in the container (count at +0x2c)
  if (*(int *)(this + 0x2c) != 0) {
    while( true ) {
      // Access element at index: base pointer at +0x28, each element is 8 bytes, value at offset 4
      result = *(undefined4 *)(*(int *)(this + 0x28) + 4 + index * 8);
      // Call comparison function on the key
      cVar1 = FUN_006aed40(key);
      if (cVar1 != '\0') break;
      index = index + 1;
      // Check if we've exhausted all elements
      if (*(uint *)(this + 0x2c) <= index) {
        return 0;
      }
    }
  }
  return result;
}