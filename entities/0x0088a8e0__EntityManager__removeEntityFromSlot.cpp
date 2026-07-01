// FUNC_NAME: EntityManager::removeEntityFromSlot
void __thiscall EntityManager::removeEntityFromSlot(int thisPtr, byte slotIndex)
{
  int entityPtr;
  uint entityCount;
  uint i;
  uint slotOffset;
  
  slotOffset = (uint)slotIndex;
  entityPtr = *(int *)(thisPtr + 0xb0 + slotOffset * 4);  // +0xB0: entity slot array
  entityCount = (uint)*(byte *)(entityPtr + 0x82) + (uint)*(byte *)(entityPtr + 0x81) +
                (uint)*(byte *)(entityPtr + 0x80);  // +0x80-0x82: entity component count (3 bytes)
  
  i = 0;
  if (entityCount != 0) {
    do {
      // Get component pointer from entity's component list at +0x68
      int componentPtr = *(int *)(*(int *)(thisPtr + 0xb0 + slotOffset * 4) + 0x68 + i * 4);
      int result = FUN_00889ee0(&componentPtr);  // Likely releaseComponent or unregisterComponent
      if (result != 0) {
        *(ushort *)(result + 0x10) = *(ushort *)(result + 0x10) & 0xfffd;  // Clear bit 1 (0x2) in flags at +0x10
      }
      i = i + 1;
    } while (i < entityCount);
  }
  
  // Clear the slot
  *(int *)(thisPtr + 0xb0 + slotOffset * 4) = 0;     // +0xB0: entity pointer
  *(int *)(thisPtr + 0xc0 + slotOffset * 4) = 0;     // +0xC0: some associated data
  *(byte *)(thisPtr + 0xbc + slotOffset) = 0;        // +0xBC: slot status/active flag
  return;
}