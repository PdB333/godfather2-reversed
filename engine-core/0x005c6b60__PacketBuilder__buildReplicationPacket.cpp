// FUNC_NAME: PacketBuilder::buildReplicationPacket
void __thiscall PacketBuilder::buildReplicationPacket(void* packetStruct, int sourceData, int extraData)
{
  int count;
  undefined4* src1Ptr;
  undefined4* src2Ptr;
  uint* bufPtr;
  int mainIter;
  int processed;
  int remaining;
  int chunkSize;
  
  // Initialize packet building (reset checksum, flags)
  beginPacket(packetStruct);
  addPacketHeaderFlags();
  updateChecksum();
  
  // Clear a field in packetStruct at +0xC
  *(int*)(sourceData + 0xC) = 0;
  
  // Get pointer to internal data source from sourceData+4
  int* internalData = *(int**)(sourceData + 4);
  int elementCount = *(int*)(internalData + 0x3C); // Number of elements to copy
  
  processed = 0;
  mainIter = 1;
  
  // Process full 4-element chunks (each chunk is 4 dwords from two sources)
  if (elementCount > 3) {
    chunkSize = ((elementCount - 4) >> 2) + 1;
    mainIter = chunkSize * 8 + 1;
    processed = chunkSize * 4;
    undefined4* dest = &gPacketBuffer; // DAT_0119d994 - static buffer
    src1Ptr = (undefined4*)(extraData + 8); // Additional source starting at offset 8
    src2Ptr = (undefined4*)(internalData + 0x48); // Primary source at offset 0x48
    
    do {
      // Copy 24 dwords per iteration (6 from src2Ptr, 18 from src1Ptr? Actually pattern: 
      // First two from src2Ptr[-2] and src2Ptr[-1]? offset -8? Let's reconstruct as:
      // Actually the loop copies from src2Ptr (starting at internalData+0x48) and src1Ptr (extraData+8)
      // Each iteration advances src2Ptr by 8 dwords (32 bytes), src1Ptr by 16 dwords (64 bytes)
      // The destination advances by 24 dwords (96 bytes)
      
      dest[-1] = src2Ptr[-2]; // Copy element from src2 (offset -2 relative to current)
      dest[0] = src2Ptr[-1];
      dest[1] = src1Ptr[-2];
      dest[2] = src1Ptr[-1];
      dest[3] = *src1Ptr;
      dest[4] = src1Ptr[1];
      dest[5] = *src2Ptr;
      dest[6] = src2Ptr[1];
      dest[7] = src1Ptr[2];
      dest[8] = src1Ptr[3];
      dest[9] = src1Ptr[4];
      dest[10] = src1Ptr[5];
      dest[11] = src2Ptr[2];
      dest[12] = src2Ptr[3];
      dest[13] = src1Ptr[6];
      dest[14] = src1Ptr[7];
      dest[15] = src1Ptr[8];
      dest[16] = src1Ptr[9];
      dest[17] = src2Ptr[4];
      dest[18] = src2Ptr[5];
      dest[19] = src1Ptr[10];
      dest[20] = src1Ptr[11];
      dest[21] = src1Ptr[12];
      dest[22] = src1Ptr[13];
      
      dest += 24;
      src1Ptr += 16;
      src2Ptr += 8;
      chunkSize--;
    } while (chunkSize != 0);
  }
  
  // Process remaining elements (1-3)
  if (processed < elementCount) {
    remaining = elementCount - processed;
    dest = &gPacketBuffer + processed * 6; // offset into buffer (6 dwords per element)
    src1Ptr = (undefined4*)(processed * 16 + 8 + extraData);
    src2Ptr = (undefined4*)(internalData + 0x3C + mainIter * 4);
    
    do {
      dest[-1] = *src2Ptr;
      dest[0] = src2Ptr[1];
      dest[1] = src1Ptr[-2];
      dest[2] = src1Ptr[-1];
      dest[3] = *src1Ptr;
      dest[4] = src1Ptr[1];
      dest += 6;
      src1Ptr += 4;
      src2Ptr += 2;
      remaining--;
    } while (remaining != 0);
  }
  
  // Write packet header: pointer to a vtable/type, then a flag byte (1 for start, 0 for end)
  bufPtr = (uint*)(gPacketWritePosition + 0x14); // global stream pointer
  **(undefined4**)(gPacketWritePosition + 0x14) = &PTR_LAB_01126b40; // Write type identifier
  *bufPtr = *bufPtr + 4; // Advance by 4 bytes (pointer size)
  *(undefined1*)*bufPtr = 1; // Write start flag
  *bufPtr = *bufPtr + 4 & 0xFFFFFFFC; // Align to 4 bytes
  
  // Call finalization function
  finalizePacketSegment();
  
  // Write end marker
  bufPtr = (uint*)(gPacketWritePosition + 0x14);
  **(undefined4**)(gPacketWritePosition + 0x14) = &PTR_LAB_01126b40; // Same type identifier
  *bufPtr = *bufPtr + 4;
  *(undefined1*)*bufPtr = 0; // Write end flag
  *bufPtr = *bufPtr + 4 & 0xFFFFFFFC;
}