// FUNC_NAME: TwoSlotManager::removeEntry
void __thiscall TwoSlotManager::removeEntry(uint *this, int *pObject) {
  uint slotIndex;
  uint *pSlotKeyPtr;
  
  if ((pObject != (int *)0x0) && (*pObject != 0)) {
    slotIndex = 0;
    pSlotKeyPtr = (uint *)(this + 0x2c); // &slot[0].key
    while (pSlotKeyPtr != pObject) { // Compare stored pointer with given object pointer
      slotIndex = slotIndex + 1;
      pSlotKeyPtr = pSlotKeyPtr + 8; // Advance to next slot's key (0x20 bytes per slot, 8*4=32)
      if (1 < slotIndex) {
        return;
      }
    }
    // slotBase = this + 0x24 + slotIndex * 0x20
    // Fields of the slot structure:
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: int* keyPtr (points to pObject)
    // +0x0C: unknown
    // +0x10: int* objectPtr (pointer to secondary object)
    // +0x14: unknown
    // +0x18: unknown (maybe this object's ID)
    // +0x1C: unknown
    if ((*(int *)(slotBase + 0x10) != 0) && (*(int **)(slotBase + 8) != (int *)0x0) &&
        (**(int **)(slotBase + 8) == *(int *)(*(int *)(slotBase + 0x10) + 0x18))) {
      cleanupSlot(0); // Call internal cleanup function (FUN_006fda60)
      *(uint *)(slotBase + 0x10) = 0;
      *(uint *)(slotBase + 0xc) = 0;
      *(uint *)(slotBase + 0x8) = 0;
      *(uint *)(slotBase + 0x14) = 0;
      *(uint *)(slotBase + 0x18) = 0;
      *(uint *)(slotBase + 0x1c) = 0;
    }
  }
  return;
}