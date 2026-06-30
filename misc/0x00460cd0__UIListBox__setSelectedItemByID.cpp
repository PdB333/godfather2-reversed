// FUNC_NAME: UIListBox::setSelectedItemByID
void __thiscall UIListBox::setSelectedItemByID(int thisPtr, int itemID)
{
  int listDescriptor;
  int count;
  int index;
  int *entryPtr;
  
  // Check if list is initialized (flag at +0x20c)
  if (*(int *)(thisPtr + 0x20c) != 0) {
    // Get list descriptor from container (+0x218)
    listDescriptor = *(int *)(*(int *)(thisPtr + 0x218) + 0x70);
    // Number of items in list (offset +0x18)
    count = *(int *)(listDescriptor + 0x18);
    index = 0;
    if (0 < count) {
      // Pointer to item array (offset +0x1c), each item is 24 bytes (6 ints)
      entryPtr = *(int **)(listDescriptor + 0x1c);
      // Linear search for item with given ID (first field of item)
      while (*entryPtr != itemID) {
        index = index + 1;
        entryPtr = entryPtr + 6; // Advance to next item
        if (count <= index) {
          return; // Not found, do nothing
        }
      }
      // Store the found index in container's selected slot (offset +0x76)
      *(short *)(*(int *)(thisPtr + 0x218) + 0x76) = (short)index;
    }
  }
  return;
}