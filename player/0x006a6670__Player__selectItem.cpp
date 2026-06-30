// FUNC_NAME: Player::selectItem

void __thiscall Player::selectItem(int this, int itemId)
{
  int *slotPtr;
  int slotIndex;
  
  if (itemId != *(int *)(this + 0x6a4)) {
    // If current item is set but something flag is zero, try to clear it
    if ((*(int *)(this + 0x6b8) == 0) && (*(int *)(this + 0x6a4) != 0)) {
      Player::clearActiveItem();
    }
    slotIndex = 0;
    slotPtr = (int *)(this + 0x6d4);
    // Search for the item in the equipped items array (32 slots, each 24 bytes)
    do {
      if (slotPtr[-6] == itemId) break;      // slot at offset -24
      if (*slotPtr == itemId) {               // slot at offset 0
        slotIndex = slotIndex + 1;
        break;
      }
      if (slotPtr[6] == itemId) {             // slot at offset +24
        slotIndex = slotIndex + 2;
        break;
      }
      if (slotPtr[0xc] == itemId) {           // slot at offset +48
        slotIndex = slotIndex + 3;
        break;
      }
      slotIndex = slotIndex + 4;
      slotPtr = slotPtr + 0x18;              // 24 bytes stride
    } while (slotIndex < 0x20);
    if (slotIndex == 0x20) {
      // Item not found -> set as new active item
      *(int *)(this + 0x6a4) = itemId;
      *(int *)(this + 0x6b8) = 1;
      // Lookup item data from database
      int itemData = ItemDatabase::getItemData(&itemId);
      if (itemData == 0) {
        // Default data
        *(int *)(this + 0x6a8) = 0;
        *(int *)(this + 0x6ac) = 0;
        *(int *)(this + 0x6b0) = 0;
        *(int *)(this + 0x6b4) = _DAT_00d5780c;
        return;
      }
      // Copy item data (16 bytes starting at offset 0x14 from itemData)
      *(long long *)(this + 0x6a8) = *(long long *)(itemData + 0x14);
      *(long long *)(this + 0x6b0) = *(long long *)(itemData + 0x1c);
      return;
    }
    // Item found in equipped list -> clear active item
    *(int *)(this + 0x6a4) = 0;
  }
  return;
}