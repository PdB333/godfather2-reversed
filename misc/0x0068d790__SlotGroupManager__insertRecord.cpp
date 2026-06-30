// FUNC_NAME: SlotGroupManager::insertRecord
uint __thiscall SlotGroupManager::insertRecord(int thisPtr, int* groupCount, void* newRecord)
{
  uint selectedSlot;
  uint minOccupied;
  uint foundGroup;
  uint uVar8;
  uint uVar9;
  char* groupPtr;
  int iVar2;
  uint uVar4;
  uint uVar7;
  char* subPtr;
  uint uVar5;
  uint occupiedCount;

  // newRecord is a pointer to 36-byte struct; offset 12 (0x0C) is a type field
  if (*(int*)((int)newRecord + 0x0C) == 2)
  {
    // Forward search: find the group with fewest occupied slots (less than 3)
    selectedSlot = 0xFFFFFFFF;
    minOccupied = 0xFFFFFFFF;
    foundGroup = 0xFFFFFFFF;
    if (*(uint*)((int)newRecord + 0x1C) != 0)  // offset 0x1C is iteration count
    {
      uVar5 = 0;
      groupPtr = (char*)(thisPtr + 0x20);  // array of groups starts at this+0x20
      uVar8 = 0;
      do
      {
        // Count occupied slots in the next 3-slot group (each slot is 0x24 bytes)
        occupiedCount = 0;
        if (uVar5 < uVar5 + 3)  // always true unless overflow, iterate over 3 slots
        {
          iVar2 = 3;  // fixed count
          subPtr = groupPtr;
          do
          {
            if (*subPtr != '\0') { occupiedCount++; }
            subPtr += 0x24;  // next slot
            iVar2--;
          } while (iVar2 != 0);
        }
        // Keep track of group with fewest occupied slots (and less than 3)
        if ((occupiedCount < minOccupied) && (occupiedCount < 3))
        {
          minOccupied = occupiedCount;
          foundGroup = uVar8;  // group index (uVar8)
        }
        uVar8++;
        uVar5 += 3;  // advance by 3 slots (entries)
        groupPtr += 0x6C;  // 0x6C = 3 * 0x24 = size of one group
      } while (uVar8 < *(uint*)((int)newRecord + 0x1C));
    }
    // If a suitable group was found, convert group index to slot index (first slot of that group)
    selectedSlot = (foundGroup != 0xFFFFFFFF) ? foundGroup : 0;  // fallback to 0
  }
  else
  {
    // Backward search: start from a specific group (given by offset 0x1C) and scan backward
    uVar7 = *(uint*)((int)newRecord + 0x1C);
    if (uVar7 == 0xFFFFFFFF)
    {
      selectedSlot = 0xFFFFFFFF;  // no group to search
    }
    else
    {
      uVar5 = uVar7 * 3;  // compute entry index at end of group
      groupPtr = (char*)(uVar7 * 0x6C + 0x8C + thisPtr);  // start at end of group? offset 0x8C = this+0x20+0x6C?
      uVar4 = uVar7;
      minOccupied = 0xFFFFFFFF;
      foundGroup = 0xFFFFFFFF;
      do
      {
        occupiedCount = 0;
        // Count occupied slots in the 3 slots ending at current position (scan backward)
        if (uVar5 < uVar5 + 3)
        {
          iVar2 = 3;
          subPtr = groupPtr;
          do
          {
            if (*subPtr != '\0') { occupiedCount++; }
            subPtr -= 0x24;  // move to previous slot
            iVar2--;
          } while (iVar2 != 0);
        }
        if ((occupiedCount < minOccupied) && (occupiedCount < 3))
        {
          minOccupied = occupiedCount;
          foundGroup = uVar4;  // group index (uVar4)
        }
        uVar4--;
        uVar5 -= 3;
        groupPtr -= 0x6C;  // move to previous group
      } while (uVar4 != 0xFFFFFFFF);
      selectedSlot = (foundGroup != 0xFFFFFFFF) ? foundGroup : uVar7;  // fallback to original group
    }
  }

  // Validate that found slot index is within range (groupCount * 3 slots)
  if ((uint)(*groupCount * 3) <= selectedSlot)
  {
    return 0xFFFFFFFF;  // failure
  }

  // Copy the 36-byte record into the selected slot (each slot is 0x24 bytes)
  uint* destSlot = (uint*)(thisPtr + selectedSlot * 0x24);
  *destSlot = *(uint*)newRecord;  // copy first 8 bytes (two uint)
  destSlot[1] = ((uint*)newRecord)[1];
  destSlot[2] = ((uint*)newRecord)[2];
  destSlot[3] = ((uint*)newRecord)[3];
  *(int*)(destSlot + 4) = *(int*)((int*)newRecord + 4);  // copy last 4 bytes (total 20)

  return selectedSlot;
}