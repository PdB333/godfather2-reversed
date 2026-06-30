// FUNC_NAME: GhostManager::getPacketDeliveryStatus
uint GhostManager::getPacketDeliveryStatus(uint ghostFlags)
{
  uint uVar1;
  
  uVar1 = ghostFlags & 0xc0000000;
  if (uVar1 == 0) {
    // Flag bits 31-30 clear: packet is pending (still in flight)
    return ghostFlags & 0x1f;
  }
  if (uVar1 != 0x40000000) {
    if (uVar1 != 0xc0000000) {
      // Invalid state
      return 0;
    }
    // Both bits 31-30 set: packet was acknowledged, get sequence from +0x4c offset table
    return *(uint *)(ghostFlags * 4 + 0x4c) & 0x1f;
  }
  // Only bit 30 set: packet was rejected/lost, get sequence from base table
  return *(uint *)(ghostFlags * 4) & 0x1f;
}