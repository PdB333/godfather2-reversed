// FUNC_NAME: TaskManager::clearAllTasks

void TaskManager::clearAllTasks(void)
{
  int iVar1;
  int* pArrayEntry;
  int iIndex;
  int* piThis;
  
  piThis = (int*)this;
  *piThis = (int)&PTR_LAB_00e39c3c; // vtable setup, likely redundant in practice
  if (0 < *(int*)((int)piThis + 0x10)) { // count at offset 16 (piThis[4])
    do {
      iVar1 = *(int*)(*(int*)((int)piThis + 0x0c) + iIndex * 4); // array[iIndex] at offset 12 (piThis[3])
      if (iVar1 != 0) {
        if (*(int*)(iVar1 + 0x40) != 0) { // has a pending action reference at +0x40
          FUN_00557020(); // acquire reference or lock? (no param shown, likely implicit 'this' or 'iVar1')
          pArrayEntry = *(int**)(iVar1 + 0x40);
          // Check reference count at pArrayEntry+4 (short)
          if (*(short*)(pArrayEntry + 1) != 0) { // offset 4 from pArrayEntry
            // Decrement release count at pArrayEntry+6
            *(short*)((int)pArrayEntry + 6) = *(short*)((int)pArrayEntry + 6) - 1;
            if (*(short*)((int)pArrayEntry + 6) == 0) {
              // Call virtual destructor/release at vtable[0]
              (**(code**)*pArrayEntry)(1);
            }
          }
          *(int*)(iVar1 + 0x40) = 0; // clear the reference
        }
        FUN_009c8eb0(iVar1); // release or delete the task object
      }
      iIndex = iIndex + 1;
    } while (iIndex < *(int*)((int)piThis + 0x10));
  }
  *(int*)((int)piThis + 0x10) = 0; // count = 0
  FUN_009c8f10(*(int*)((int)piThis + 0x0c)); // free the array memory
  *(int*)((int)piThis + 0x0c) = 0; // clear array pointer
  *(int*)((int)piThis + 0x14) = 0; // offset 20 (piThis[5]) unknown, likely additional count
  // Call a virtual function on some associated object at offset 8 (piThis[2])
  (**(code**)(**(int**)((int)piThis + 0x08) + 0x0c))(); // likely some manager notification
  if (*(int*)((int)piThis + 0x0c) != 0) {
    FUN_009c8f10(*(int*)((int)piThis + 0x0c)); // guard free (redundant but safe)
  }
  FUN_0049c640(); // common cleanup function, e.g., memory pool flush
  return;
}