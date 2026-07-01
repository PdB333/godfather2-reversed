// FUNC_NAME: NetConnection::sendUpdateList

void __thiscall NetConnection::sendUpdateList(uint this, int *pMessageType)
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uIndex;
  undefined1 *puStr;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  code *local_c;

  // Check if this is a known message type
  if (gUpdateMessageType == *pMessageType) {
    // First branch: handle update message type
    // Clamp param: if this != 0x214, use this; else 0
    uVar2 = isBitSet( -(uint)(this != 0x214) & this );
    if ((uVar2 & 1) == 0) {
      // Not set, send a message with flags 0x8000
      sendMessage(1, -(uint)(this != 0x214) & this, 0x8000);
      return;
    }
  }
  else if (gListMessageType == *pMessageType) {
    // Second branch: handle list message type
    uIndex = 0;
    // Check if the message has a valid list pointer
    if ((pMessageType[1] != 0) && (iVar1 = *(int *)(pMessageType[1] + 0xc), iVar1 != 0) &&
       (*(int *)(iVar1 + 0x2c) == 0)) {
      // Copy sequence number from global
      local_1c = gSequenceNumber;
      // Mark as dirty? or set flag
      markDirty(1, -(uint)(this != 0x214) & this);
      // Get number of items from list header (offset -8)
      uVar2 = *(uint *)(this - 8);
      if (uVar2 != 0) {
        local_18 = (undefined1 *)0x0;
        local_14 = 0;
        local_10 = 0;
        local_c = (code *)0x0;
        if (uVar2 != 0) {
          do {
            // Get pointer to current item
            puVar3 = *(undefined4 **)(*(int *)(this - 0xc) + uIndex * 4);
            local_24 = puVar3[4]; // offset +0x10
            puStr = (undefined1 *)*puVar3; // name string pointer
            if (puStr == (undefined1 *)0x0) {
              puStr = &DAT_0120546e; // default empty string
            }
            // Append name to string buffer
            stringAppend(&local_18, puStr, 1);
            // Get data from item's structure
            local_20 = *(undefined4 *)(iVar1 + 0x48); // offset +0x48
            puStr = local_18;
            if (local_18 == (undefined1 *)0x0) {
              puStr = &DAT_0120546e;
            }
            // Serialize int with data
            serializeInt(puStr, local_20, 4, &local_24, puVar3[5] + 8);
            uIndex = uIndex + 1;
          } while (uIndex < uVar2);
          // Free string buffer if allocated
          if (local_18 != (undefined1 *)0x0) {
            (*local_c)(local_18);
          }
        }
      }
    }
  }
  return;
}