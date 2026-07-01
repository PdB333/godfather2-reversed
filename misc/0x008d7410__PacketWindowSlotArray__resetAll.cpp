// FUNC_NAME: PacketWindowSlotArray::resetAll
void __fastcall PacketWindowSlotArray::resetAll(int this)
{
  uint index;
  int slotOffset;
  int slotSize;

  *(int *)(this + 0x18) = 0; // +0x18: nextSequenceId
  uint slotCount = *(uint *)(this + 0x30); // +0x30: slotCount1
  if (slotCount != 0) {
    index = 0;
    do {
      // Each slot structure at +0x2c base, offset by slotIndex * 0x2c
      // Structure layout: 2 entries of 5 uint (0x14 each) = 0x28 total per slot, plus 4-byte header?
      int* slotBase = *(int**)(this + 0x2c); // +0x2c: slotArray1
      int* pEntry = slotBase + (index * 0x2c / 4); // slot base pointer
      int entry = 2;
      do {
        *(pEntry + 1) = 0; // Clear first uint of entry (likely sequenceId or data)
        pEntry += 5;        // Each entry is 0x14 bytes (5 ints)
        entry--;
      } while (entry != 0);
      index++;
    } while (index < slotCount);
  }

  slotCount = *(uint *)(this + 0x3c); // +0x3c: slotCount2
  if (slotCount != 0) {
    index = 0;
    do {
      // Each slot structure at +0x38 base, offset by slotIndex * 0x18
      int* slotBase2 = *(int**)(this + 0x38); // +0x38: slotArray2
      int* pEntry2 = slotBase2 + (index * 0x18 / 4);
      *(pEntry2 + 1) = 0; // Clear first field of second slot
      index++;
    } while (index < slotCount);
  }

  *(int *)(this + 0x44) = 0; // +0x44: someCount1
  *(int *)(this + 0x58) = 0; // +0x58: someCount2
  *(int *)(this + 0x6c) = 0; // +0x6c: someCount3
  *(int *)(this + 0x80) = 0; // +0x80: someCount4
  *(int *)(this + 0x94) = 0; // +0x94: someCount5
}