// FUNC_NAME: HeatMapManager::recordHeatEvent
void __thiscall HeatMapManager::recordHeatEvent(HeatMapManager *this, uint *eventKey, int eventType)
{
  short *psVar6;
  ushort *puVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  int slotIndex;
  int slotBase;
  ushort *pHistory;
  int sum;
  int i;
  ushort uVar7;
  byte level;

  slotIndex = findSlotForEventKey(eventKey); // FUN_008bcb50 - returns -1 if not found
  if (slotIndex < 0) {
    // Allocate new slot for this event key
    int newSlot = allocateNewSlot(); // FUN_008bccb0
    // Store the event key (4 dwords) at offsets 0x18, 0x1c, 0x20, 0x24
    *(uint *)(newSlot + 0x18) = eventKey[0];
    *(uint *)(newSlot + 0x1c) = eventKey[1];
    *(uint *)(newSlot + 0x20) = eventKey[2];
    *(uint *)(newSlot + 0x24) = eventKey[3];
    // Increment the counter corresponding to eventType (short at offset eventType*2)
    psVar6 = (short *)(newSlot + eventType * 2);
    *psVar6 = *psVar6 + 1;
  }
  else {
    slotBase = slotIndex * 0x2c + *(int *)(this + 8); // array base at this+8, each slot 0x2c bytes
    uVar7 = *(ushort *)(slotBase + eventType * 2);   // counter for this event type
    if (uVar7 < 999) {
      *(ushort *)(slotBase + eventType * 2) = uVar7 + 1; // increment counter

      // Sum 12 history shorts from offsets +4 to +15
      sum = 0;
      pHistory = (ushort *)(slotBase + 8); // start at offset +8
      i = 2; // process two groups of 6 shorts each
      do {
        // Read 6 shorts relative to current pHistory: -4, -3, -2, -1, 0, +1
        puVar1 = pHistory - 3;
        puVar2 = pHistory - 4;
        puVar3 = pHistory - 2;
        puVar4 = pHistory - 1;
        puVar5 = pHistory + 1;
        uVar7 = *pHistory;
        pHistory = pHistory + 6; // advance to next group (offset +14)
        i--;
        sum = (uint)*puVar2 + (uint)*puVar1 + (uint)*puVar3 + (uint)*puVar4 + (uint)*puVar5 + (uint)uVar7 + sum;
      } while (i != 0);

      // Determine heat level based on sum threshold
      if (sum < 10) {
        level = 1;
      }
      else if (sum < 25) {
        level = 2;
      }
      else {
        level = (sum > 69) ? 4 : 3; // 0x45 = 69
      }

      // If new level is higher than stored level, update and set dirty flag
      if (*(byte *)(slotBase + 0x28) < level) {
        *(byte *)(this + 0x19) = 1; // dirty flag
        *(byte *)(slotBase + 0x28) = level;
        return;
      }
    }
  }
  return;
}