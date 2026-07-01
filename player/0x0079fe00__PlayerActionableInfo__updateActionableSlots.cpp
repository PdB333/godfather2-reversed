// FUNC_NAME: PlayerActionableInfo::updateActionableSlots
void __fastcall PlayerActionableInfo::updateActionableSlots(int *thisPtr)
{
  int *slotPtr;
  int slotCount;
  
  // Call virtual function at vtable+0x2dc (likely update or reset)
  (**(code **)(*thisPtr + 0x2dc))();
  
  // Start at offset +0x866 (first actionable slot entry, each 7 bytes)
  slotPtr = thisPtr + 0x866;
  
  // Loop through slots: count stored at offset +0x923 (0x923*4 = 0x248C)
  for (slotCount = thisPtr[0x923]; slotCount != 0; slotCount = slotCount + -1) {
    // If slot's first byte (active flag) is 0, set it to 1
    if ((char)*slotPtr == '\0') {
      *(char *)slotPtr = '\x01';
    }
    // Advance to next slot (7 bytes per slot: 1 byte flag + 6 bytes data)
    slotPtr = slotPtr + 7;
  }
  return;
}