// FUNC_NAME: SomeContainer::clear
void __fastcall SomeContainer::clear(int *this)
{
  int *nextItem;
  int *currentItem;
  uint index;

  // Iterate over all items in a linked list, starting from the head stored at (*this + 8) -> value
  currentItem = **(int ***)(*this + 8);
  while (currentItem != 0) {
    // Save the next item before deletion
    nextItem = **(int ***)(currentItem + 8);
    // Free/destroy the item data (at offset +8)
    FUN_009c8f10(*(int **)(currentItem + 8));
    // Free/destroy the item node itself
    FUN_009c8eb0(currentItem);
    // Decrement the count stored at this[4] (+0x10)
    this[4] = this[4] + -1;
    currentItem = nextItem;
  }
  // Zero out the array of pointers starting at (*this + 8) head pointer
  index = 0;
  do {
    *(undefined4 *)(*(int *)(*this + 8) + index * 4) = 0;
    index = index + 1;
  } while (index <= (uint)this[2]);  // this[2] is capacity/element count
  this[1] = 0;  // Reset something (maybe size or a sentinel)
  return;
}