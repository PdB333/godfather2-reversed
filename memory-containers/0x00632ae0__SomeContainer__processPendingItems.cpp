// FUNC_NAME: SomeContainer::processPendingItems
void __fastcall SomeContainer::processPendingItems(undefined4 param_1, int this)
{
  int currentItem;
  
  // Iterate through items in a circular buffer or list
  // +0x14 = start pointer, +0x28 = end pointer
  currentItem = *(int *)(this + 0x14);
  if (currentItem != *(int *)(this + 0x28)) {
    do {
      // Check flags at +0x8: bit 0 = pending, bit 1 = ready
      // If not pending (bit0=0) but ready (bit1=1), copy data
      if (((*(uint *)(currentItem + 8) & 1) == 0 && ((*(uint *)(currentItem + 8) & 2) != 0)) {
        // Copy pointer from +0x10 to value at +0xc
        *(undefined4 *)(currentItem + 0xc) = **(undefined4 **)(currentItem + 0x10);
      }
      // Move to previous item (each item is 0x18 bytes)
      currentItem = currentItem + -0x18;
    } while (currentItem != *(int *)(this + 0x28));
  }
  // Mark processing complete at +0x32
  *(undefined1 *)(this + 0x32) = 1;
  return;
}