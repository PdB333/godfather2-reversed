// FUNC_NAME: SomeUIList::handleInputEvent
void __thiscall SomeUIList::handleInputEvent(int this, int inputAction)
{
  int currentIndex;
  int newIndex;
  
  switch(inputAction) {
  case 8: // Some action like "select" or "confirm"
    currentIndex = *(int *)(this + 0x2c); // +0x2c: currentSelectedIndex
    if (0 < currentIndex) {
      newIndex = currentIndex;
      if (0 < currentIndex) {
        newIndex = 1;
      }
      FUN_004dbe70(currentIndex - newIndex, newIndex); // Some animation/scroll function
      *(undefined4 *)(this + 0x28) = *(undefined4 *)(this + 0x1c); // +0x28: targetIndex, +0x1c: some offset
      if (newIndex != 0) {
        FUN_0098a480(*(int *)(this + 0x2c) - newIndex); // Update selected index
        FUN_00402050(&DAT_011301c0, 0); // Play sound
      }
    }
  default:
    return;
  case 0x23: // Up arrow
    FUN_0098a480(*(undefined4 *)(this + 0x28)); // Set selected index to target
    FUN_00402050(&DAT_011304d8, 0); // Play sound
    return;
  case 0x24: // Down arrow
    FUN_0098a480(0); // Reset to first item
    FUN_00402050(&DAT_011304d8, 0); // Play sound
    return;
  case 0x25: // Left arrow
    FUN_0098a480(*(int *)(this + 0x2c) + -1); // Decrement selected index
    FUN_00402050(&DAT_011304d8, 0); // Play sound
    return;
  case 0x27: // Right arrow
    FUN_0098a480(*(int *)(this + 0x2c) + 1); // Increment selected index
    FUN_00402050(&DAT_011304d8, 0); // Play sound
    return;
  case 0x2e: // Some other action (maybe "scroll to end")
    break;
  }
  
  currentIndex = *(int *)(this + 0x2c);
  if (*(int *)(this + 0x28) <= currentIndex) {
    return;
  }
  newIndex = *(int *)(this + 0x28) - currentIndex;
  if (newIndex < 1) {
    if (newIndex < 1) goto LAB_0098a884;
  }
  else {
    newIndex = 1;
  }
  FUN_004dbe70(currentIndex, newIndex);
  *(undefined4 *)(this + 0x28) = *(undefined4 *)(this + 0x1c);
LAB_0098a884:
  FUN_00402050(&DAT_011301c0, 0);
  return;
}