// FUNC_NAME: TNLConnection::processNextReliablePacket
void TNLConnection::processNextReliablePacket(TNLConnection *this, PacketBuffer *packetBuf)
{
  // local_8 is likely `this` or a packet descriptor pointer
  // param_1 (iVar5) = this
  // param_2 = packetBuf
  // param_1 is reassigned to *packetBuf (packet data start)

  int *reliableQueue;  // piVar2, pointer to reliable send queue structure
  int count;  // iVar3, remaining packets to process
  int *packetData;  // puVar1, current packet data pointer
  int currentIndex;  // iVar4, index into queue
  int queueSize;  // local variable for capacity

  // Save this pointer
  int self = (int)this;
  
  // Dereference packet buffer to get the raw data pointer
  packetBuf = (PacketBuffer *)*packetBuf;
  
  // Call helper to prepare packet data (likely deserialize header)
  preparePacketData(&packetBuf);

  // Get the reliable send queue from the connection (offset +0x04 from local_8?)
  reliableQueue = *(int **)(local_8 + 4);
  
  // Get remaining packet count from queue (offset +0x0C = piVar2[3])
  count = reliableQueue[3];
  
  while (count != 0) {
    // Calculate pointer to current packet in circular buffer
    // Buffer base = *reliableQueue (raw data pointer)
    // Current index = reliableQueue[2] (write index?)
    // Each packet is 8 bytes (two 4-byte values)
    packetData = (int *)(*reliableQueue + reliableQueue[2] * 8);
    
    // Call the packet handler virtual function (vtable+0x04)
    // This is likely processReliablePacket(int packetId, int sequenceNumber)
    (**(code **)(**(int **)(self + 8) + 4))(*packetData, packetData[1]);
    
    // Update count from queue capacity
    count = reliableQueue[2];
    
    // Get base address and calculate new head slot
    currentIndex = *reliableQueue;
    *packetData = *(int *)(currentIndex + count * 8);
    packetData[1] = *(int *)(currentIndex + 4 + count * 8);
    
    // Advance write index (circular buffer)
    reliableQueue[2] = reliableQueue[2] + 1;
    
    // Wrap around if exceeded capacity
    if (reliableQueue[1] <= reliableQueue[2]) {
      reliableQueue[2] = 0;
    }
    
    // Decrement remaining count
    reliableQueue[3] = reliableQueue[3] - 1;
    count = reliableQueue[3];
  }
  
  // Free the raw data buffer if present (FUN_009c8f10 = operator delete[])
  if (*reliableQueue != 0) {
    operatorDeleteArray(*reliableQueue);
  }
  
  // Free the queue structure (FUN_009c8eb0 = operator delete)
  operatorDelete(reliableQueue);
  
  // Restore original packet buffer pointer
  packetBuf = (PacketBuffer *)*packetBuf;
  
  // Cleanup packet buffer (FUN_0065db70 = releasePacketBuffer)
  releasePacketBuffer(&packetBuf);
}