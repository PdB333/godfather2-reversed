// FUNC_NAME: SomeClass::countActiveItems
int __thiscall countActiveItems(int this, undefined4 param_2)
{
  int count;
  int result;
  undefined4 *iterator;
  int currentItem;
  int itemCount;
  
  count = 0;
  // Call some initialization function with the object at offset +0x60
  FUN_008b3fb0(*(undefined4 *)(this + 0x60), param_2, 0);
  
  // Iterate through items while there are more to process
  while ((currentItem != 0 || (itemCount != 0))) {
    result = (*(code *)*iterator)();
    // Check if bit 0 of byte at offset +0x30 is set (active flag)
    if ((*(byte *)(result + 0x30) & 1) != 0) {
      count = count + 1;
    }
    // Move to next item via iterator's second function pointer
    (*(code *)iterator[1])();
  }
  return count;
}