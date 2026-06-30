// FUNC_NAME: NetworkManager::addOrUpdateReliablePacket
void NetworkManager::addOrUpdateReliablePacket(void)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  // Check if reliable packet buffer is full (offset +0x10 -> +0x20 and +0x24 track current/next index)
  if (*(uint *)(*(int *)(unaff_ESI + 0x10) + 0x20) <= *(uint *)(*(int *)(unaff_ESI + 0x10) + 0x24))
  {
    // Flush pending reliable packets
    FUN_00627360();
  }
  
  // Get pointer to next reliable packet slot (+0x8 is offset to packet data array)
  puVar1 = *(undefined4 **)(unaff_ESI + 8);
  
  // Set packet type to 5 (reliable packet type ID)
  *puVar1 = 5;
  
  // Generate sequence number for this packet
  uVar2 = FUN_00637c50(0,0);
  puVar1[1] = uVar2;
  
  // Advance packet slot pointer by 8 bytes (one packet entry size)
  *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + 8;
  
  return;
}