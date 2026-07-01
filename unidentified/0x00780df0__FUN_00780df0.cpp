// FUNC_NAME: SomeClass::updateSomeList
void __fastcall SomeClass::updateSomeList(int *this)
{
  int *listHead;
  int *currentItem;
  int itemValue;
  int newItem;
  
  listHead = (int *)this[0x17]; // +0x5C: pointer to some list head
  itemValue = listHead[0x1d3]; // +0x74C: current item value
  currentItem = listHead + 0x1d3; // pointer to current item slot
  
  // Check if we need to update the list
  if (((((itemValue == 0) || (itemValue == 0x48)) || (((uint)listHead[0x238] >> 10 & 1) == 0)) ||
      ((*(uint *)(itemValue + 0x188) >> 3 & 1) == 0)) && (newItem = FUN_0077f3d0(), newItem != 0)) {
    // Call virtual function at vtable+0x2c (some kind of notification/event)
    (**(code **)(*this + 0x2c))(0x3adcd46a, 1, 1, 0, 0x3f800000, 0x3f800000);
    
    int oldValue = *currentItem;
    if (((oldValue != 0) && (oldValue != 0x48)) && (oldValue - 0x48 != newItem)) {
      // Call virtual function at vtable+0x260 (cleanup/remove)
      (**(code **)(*listHead + 0x260))();
    }
    
    int newValue = newItem + 0x48;
    if (*currentItem != newValue) {
      if (*currentItem != 0) {
        FUN_004daf90(currentItem); // Remove old item from list
      }
      *currentItem = newValue;
      if (newValue != 0) {
        listHead[0x1d4] = *(int *)(newItem + 0x4c); // +0x4C: next pointer in item
        *(int **)(newItem + 0x4c) = currentItem; // Link item into list
      }
    }
  }
  return;
}