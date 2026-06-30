// FUNC_NAME: SlotManager::attachSlot
void __thiscall SlotManager::attachSlot(int thisPtr, int owner)
{
  int *slotPtr; // Pointer to the slot entry in the manager's array
  int slotDataPtr; // Address of the owner's slot data field

  // Calculate the slot entry: manager has array at +0x1AC, each entry 8 bytes (2 ints)
  // The index is read from owner at +0x184 (e.g., slot ID)
  slotPtr = (int *)(thisPtr + 0x1AC + *(int *)(owner + 0x184) * 8);
  slotDataPtr = owner + 0x48;

  // If the slot doesn't already point to the same owner's data
  if (*slotPtr != slotDataPtr) {
    // If the slot was previously occupied, remove the old link
    if (*slotPtr != 0) {
      FUN_004daf90(slotPtr); // Remove slot from owner's linked list and possibly free
    }
    // Store the pointer to owner's slot data field in the slot
    *slotPtr = slotDataPtr;

    // Insert this slot as the new head of the owner's linked list
    if (slotDataPtr != 0) {
      slotPtr[1] = *(int *)(owner + 0x4C); // Next pointer = current head
      *(int **)(owner + 0x4C) = slotPtr;   // Owner's list head = this slot
    }
  }
  return;
}