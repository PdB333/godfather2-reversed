// FUNC_NAME: BuildingManager::assignBuildingResourceSlots
void __fastcall BuildingManager::assignBuildingResourceSlots(int this)
{
  // +0x7c: start pointer of building array (element size 0x50)
  // +0x80: end pointer of building array
  int buildingStart = *(int *)(this + 0x7c);
  int buildingEnd   = *(int *)(this + 0x80);
  int byteDiff = buildingEnd - buildingStart;
  int quotient = byteDiff / 0x50;
  int remainder = byteDiff % 0x50;
  int signAdjust = (byteDiff >> 0x1f); // handle negative diff (defensive)
  int buildingCount = quotient + signAdjust != signAdjust ? quotient : 0;

  int byteOffset = 0;
  int idx = 0;
  if (buildingCount == 0) return;

  do {
    int currentBuilding = buildingStart + byteOffset;
    int buildingData = *(int *)(currentBuilding + 0x14); // pointer to building data block
    int resourceID = *(int *)(buildingData + 0x68);  // unique resource handle at data+0x68

    // Skip buildings with uninitialized/invalid resource ID
    if (resourceID != -0x1e98fd1) {  // 0xFE16702F (invalid sentinel)
      int slotCount = FUN_0088daf0();  // returns number of available resource slots
      if (slotCount != 0) {
        uint slotIdx = 0;
        do {
          FUN_0088db00(slotIdx);                    // prepare slot context
          int assignedSlot = FUN_00889ee0(resourceID); // try to map resource to slot
          *(int *)(currentBuilding + 0x40) = assignedSlot; // store slot index at building+0x40
          if (assignedSlot != 0) break;             // success, stop searching
          slotIdx++;
        } while (slotIdx < (uint)slotCount);
      }
    }
    byteOffset += 0x50;
    idx++;
  } while (idx < buildingCount);
}