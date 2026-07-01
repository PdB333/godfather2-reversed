// FUNC_NAME: GenericContainer::resize
void __thiscall GenericContainer::resize(int *param_1, uint newCount)
{
  int *piVar1;
  int *piVar2;
  uint oldCount;
  uint remaining;
  int index;
  int slotOffset;
  int delta;
  
  oldCount = param_1[1];
  if (oldCount < newCount) {
    // Expand: grow the container
    FUN_00855960(newCount);
    oldCount = param_1[1];
    if (oldCount < newCount) {
      // Initialize new slots
      slotOffset = oldCount * 0x2c;  // Each slot is 0x2c bytes
      delta = newCount - oldCount;
      do {
        index = *param_1 + slotOffset;  // +0x00: pointer to data array
        if (index != 0) {
          *(undefined1 *)(index + 0xc) = 0;   // +0x0C: byte field
          *(undefined1 *)(index + 0xd) = 0;   // +0x0D: byte field
          *(undefined4 *)(index + 0x10) = 0;  // +0x10: pointer (set to null)
          *(undefined1 *)(index + 0x19) = 0;  // +0x19: byte field
          *(undefined4 *)(index + 0x1c) = 0xbadbadba;  // +0x1C: debug sentinel
          *(undefined4 *)(index + 0x20) = 0xbeefbeef;  // +0x20: debug sentinel
          *(undefined4 *)(index + 0x24) = 0xeac15a55;  // +0x24: debug sentinel
          *(undefined4 *)(index + 0x28) = 0x91100911;  // +0x28: debug sentinel
        }
        slotOffset += 0x2c;
        delta--;
      } while (delta != 0);
      param_1[1] = newCount;  // +0x04: new count
      return;
    }
  }
  else {
    if (oldCount <= newCount) {
      // No size change needed
      return;
    }
    // Shrink: release extra slots
    delta = oldCount - 1;
    if ((int)newCount <= delta) {
      // Iterate from last element down to newCount
      slotOffset = delta * 0x2c;
      remaining = (delta - newCount) + 1;
      do {
        index = *(int *)(slotOffset + 0x10 + *param_1);  // +0x10: pointer field (smart pointer?)
        piVar2 = (int *)(slotOffset + 0x10 + *param_1);
        if (index != 0) {
          piVar1 = (int *)(index + 4);
          *piVar1 = *piVar1 + -1;  // Decrement reference count
          piVar1 = (int *)*piVar2;
          if (piVar1[1] == 0) {  // Check if ref count reached zero
            (**(code **)(*piVar1 + 4))();  // Call destructor via vtable
          }
          *piVar2 = 0;  // Clear pointer
        }
        slotOffset -= 0x2c;
        remaining--;
      } while (remaining != 0);
    }
  }
  param_1[1] = newCount;  // +0x04: update count
  return;
}