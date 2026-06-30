// FUNC_NAME: InputManager::releaseControllerSlot
undefined1 InputManager::releaseControllerSlot(void)

{
  undefined1 *slotPtr;
  undefined1 result;
  uint slotIndex;
  uint *controllerSlot; // unaff_ESI
  
  result = 0;
  // Check if the slot is valid by XORing with a magic constant and comparing against a count
  if (((*controllerSlot ^ 0xad103100) < (uint)*(byte *)(DAT_01223504 + 0x1c)) &&
     // Get the slot index (low byte of XOR result)
     (slotIndex = (*controllerSlot ^ 0xad103100) & 0xff, 
      slotPtr = (undefined1 *)(slotIndex + 0x18 + DAT_01223504),
      // Check if the slot is currently occupied (non-zero)
      *(char *)(slotIndex + 0x18 + DAT_01223504) != '\0')) {
    // Decrement the active slot count at +0x1d
    *(char *)(DAT_01223504 + 0x1d) = *(char *)(DAT_01223504 + 0x1d) + -1;
    // Clear the slot occupancy flag at +0x18 + slotIndex
    *slotPtr = 0;
    // Clear the controller slot data (set to 0)
    *controllerSlot = 0;
    result = 1;
  }
  return result;
}