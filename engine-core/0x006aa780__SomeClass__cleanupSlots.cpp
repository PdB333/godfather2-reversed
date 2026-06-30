// FUNC_NAME: SomeClass::cleanupSlots
void __fastcall cleanupSlots(int thisPtr)
{
  int slotIndex;
  undefined4 *currentSlotPtr;
  undefined4 *slotBasePtr;
  
  slotBasePtr = (undefined4 *)(thisPtr + 0x360);
  slotIndex = 7;
  currentSlotPtr = (undefined4 *)(thisPtr + 0x390);
  do {
    slotBasePtr = slotBasePtr + -0x1b; // Move to previous slot (0x6C bytes per slot)
    *slotBasePtr = &PTR_FUN_00d5d9b0; // Set vtable pointer
    if (currentSlotPtr[-0x1a] != 0) { // Check if slot data exists at offset -0x68
      (*(code *)currentSlotPtr[-0x17])(currentSlotPtr[-0x1a]); // Call destructor at offset -0x5C
    }
    if (currentSlotPtr[-0x1e] != 0) { // Check if slot data exists at offset -0x78
      (*(code *)currentSlotPtr[-0x1b])(currentSlotPtr[-0x1e]); // Call destructor at offset -0x6C
    }
    if (currentSlotPtr[-0x22] != 0) { // Check if slot data exists at offset -0x88
      (*(code *)currentSlotPtr[-0x1f])(currentSlotPtr[-0x22]); // Call destructor at offset -0x7C
    }
    if (currentSlotPtr[-0x26] != 0) { // Check if slot data exists at offset -0x98
      (*(code *)currentSlotPtr[-0x23])(currentSlotPtr[-0x26]); // Call destructor at offset -0x8C
    }
    slotIndex = slotIndex + -1;
    currentSlotPtr = currentSlotPtr + -0x1b; // Move to previous slot
  } while (-1 < slotIndex);
  return;
}