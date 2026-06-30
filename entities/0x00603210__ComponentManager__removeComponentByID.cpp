// FUNC_NAME: ComponentManager::removeComponentByID
void __thiscall ComponentManager::removeComponentByID(int thisPtr, int componentID)
{
  int *componentArray; // pointer to array of component pointers at +0x30
  int componentCount; // count at +0x34
  int index;
  int *currentPtr;
  void *foundComponent;
  undefined4 local_20; // stack variable for global data
  undefined4 local_1c;
  undefined1 local_18;

  componentCount = *(int *)(thisPtr + 0x34);
  if (componentCount != 0) {
    componentArray = *(int **)(thisPtr + 0x30);
    index = 0;
    // Search for the component whose internal ID (at offset +0x0c) matches componentID
    currentPtr = componentArray;
    while (*(int *)(*currentPtr + 0xc) != componentID) {
      index++;
      currentPtr++;
      if (componentCount <= (uint)index) {
        return; // Not found
      }
    }
    // Remove the found component
    if (-1 < index) {
      foundComponent = (void *)componentArray[index];
      // Shift remaining components left
      if (index < componentCount - 1) {
        do {
          componentArray[index] = componentArray[index + 1];
          index++;
        } while (index < componentCount - 1);
      }
      // Decrement count
      *(int *)(thisPtr + 0x34) = componentCount - 1;
      // Destroy and deallocate the removed component
      if (foundComponent != (void *)0x0) {
        // Call virtual destructor (vtable entry at +0x0c)
        (**(code **)(*(int *)foundComponent + 0xc))();
        // Deallocate memory (likely operator delete)
        FUN_009c8eb0(foundComponent);
      }
      // If the container is now empty, reset all state flags
      if (*(int *)(thisPtr + 0x34) == 0) {
        *(undefined1 *)(thisPtr + 0x54) = 0;
        *(undefined1 *)(thisPtr + 0x64) = 0;
        *(undefined1 *)(thisPtr + 0x74) = 0;
        *(uint *)(thisPtr + 0x4c) &= 0xfffffffd; // Clear bit 1
        *(undefined1 *)(thisPtr + 0x84) = 0;
        *(undefined1 *)(thisPtr + 0x94) = 0;
        *(uint *)(thisPtr + 0x4c) &= 0xfffffffb; // Clear bit 2
        *(undefined1 *)(thisPtr + 0xa4) = 0;
        *(undefined1 *)(thisPtr + 0xb4) = 0;
        *(undefined1 *)(thisPtr + 0xc4) = 0;
        *(undefined1 *)(thisPtr + 0xd4) = 0;
        *(undefined1 *)(thisPtr + 0xe4) = 0;
        *(uint *)(thisPtr + 0x4c) &= 0xfffffff7; // Clear bit 3
      }
      // Trigger a callback or sound event with global data
      local_20 = DAT_01222230;
      local_1c = 0;
      local_18 = 0;
      FUN_00408a00(&local_20, 0);
    }
  }
  return;
}