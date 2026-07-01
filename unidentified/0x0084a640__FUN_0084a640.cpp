// FUNC_NAME: SomeClass::countActiveItems
int __fastcall SomeClass::countActiveItems(int this)
{
  int activeCount = 0;
  unsigned int index = 0;
  
  if (*(int *)(this + 8) != 0) { // +0x08: itemCount (number of items in the container)
    do {
      int itemStatus = FUN_006b4860(); // likely checks if item is active/valid
      if (itemStatus == 0) {
        activeCount = activeCount + 1;
      }
      index = index + 1;
    } while (index < *(unsigned int *)(this + 8)); // loop through all items
  }
  return activeCount;
}