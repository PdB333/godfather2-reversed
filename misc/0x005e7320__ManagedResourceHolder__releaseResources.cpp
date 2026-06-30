// FUNC_NAME: ManagedResourceHolder::releaseResources
void __thiscall ManagedResourceHolder::releaseResources(void* this)
{
  int* resourceManager;
  int* resourceArray;
  int i;

  // +0x14 = pointer to a manager object
  if (*(int**)((int)this + 0x14) != 0) {
    resourceArray = (int*)((int)this + 4);  // +0x04 = array of 4 resource pointers
    i = 4;
    do {
      if (*resourceArray != 0) {
        // Call virtual release method (vtable+0x04) with flag 0
        (**(code (***)(int*,int))(*resourceArray + 4))(*resourceArray, 0);
        *resourceArray = 0;  // Clear the pointer
      }
      resourceArray = resourceArray + 1;
      i = i + -1;
    } while (i != 0);
    // Shutdown manager via virtual method at vtable+0x0C
    (**(code (***)(void))(*((int*)((int)this + 0x14)) + 0xc))();
    *(int**)((int)this + 0x14) = 0;  // Clear manager pointer
  }
  return;
}