// FUNC_NAME: TNLConnection::freePacket
void __thiscall TNLConnection::freePacket(int thisPtr, undefined4 *packet)
{
  // If the packet being freed is the current send packet, update the pointer to the next one
  if (packet == *(undefined4 **)(thisPtr + 0x84)) {
    *(undefined4 *)(thisPtr + 0x84) = packet[1];
  }
  
  // Call the base packet destructor
  FUN_00990c10(packet);
  
  // Set vtable pointer (likely to a freed/empty vtable)
  *packet = &PTR_FUN_00d91e00;
  
  // Clear and nullify any associated data buffers (offset 0x3C and 0x38 in packet)
  if (packet[0xf] != 0) {
    *(undefined4 *)(packet[0xf] + 8) = 0;
    packet[0xf] = 0;
  }
  if (packet[0xe] != 0) {
    *(undefined4 *)(packet[0xe] + 8) = 0;
    packet[0xe] = 0;
  }
  
  // Link the freed packet into the free list (singly linked list at thisPtr+0x5c)
  *packet = *(undefined4 *)(thisPtr + 0x5c);
  
  // Update connection statistics: decrement allocated count, increment freed count
  *(int *)(thisPtr + 0x38) = *(int *)(thisPtr + 0x38) - 1;  // allocatedPackets
  *(int *)(thisPtr + 0x34) = *(int *)(thisPtr + 0x34) + 1;  // freedPackets
  
  // Store the freed packet at the head of the free list
  *(undefined4 **)(thisPtr + 0x5c) = packet;
  
  // If the free list was empty before, schedule a cleanup event and signal a semaphore
  if (*(int *)(thisPtr + 0x60) == 0) {
    FUN_005c02f0(thisPtr, &LAB_00991080, 1);  // Schedule callback
    FUN_004086d0(&DAT_0112a5a4);              // Signal semaphore (likely network thread wakeup)
  }
}