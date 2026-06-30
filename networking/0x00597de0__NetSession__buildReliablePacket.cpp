// FUNC_NAME: NetSession::buildReliablePacket
undefined4 NetSession::buildReliablePacket(void)

{
  int packetBufferPtr; // in_EAX
  undefined4 packetSize; // uStack_10 (local size)
  int bufferOffset0; // iStack_30
  undefined4 **ptrToData2; // ppuStack_2c
  undefined4 dataSize2; // uStack_28
  int bufferOffset1; // iStack_24
  undefined4 *ptrToData1; // puStack_20
  undefined4 dataBuffer[2]; // auStack_1c
  undefined4 *ptrToData0; // puStack_14
  undefined4 dataSize0; // uStack_10 (reused)
  undefined4 local_8; // first data field
  undefined4 local_4; // total size
  
  // Setup first data chunk: packet type and data size
  dataSize0 = 2;
  ptrToData0 = &local_8;
  local_4 = 0x18; // total packet size = 24 bytes
  local_8 = 0x20a; // packet type/id (0x20a = 522)
  dataBuffer[0] = 0x597e0b; // return address (part of inline)
  
  // Call virtual function at offset +0x10 on DAT_01205590 (likely stream/memory writer)
  (**(code **)(*DAT_01205590 + 0x10))();
  
  // Setup second chunk: 2-byte size, store to packetBufferPtr + 2
  dataBuffer[0] = 2;
  ptrToData1 = &dataSize0;
  bufferOffset1 = packetBufferPtr + 2;
  dataSize2 = 0x597e23; // return address
  (**(code **)(*DAT_01205590 + 0x10))();
  
  // Setup third chunk: 4-byte size, store to packetBufferPtr + 4
  dataSize2 = 4;
  ptrToData2 = &ptrToData0;
  bufferOffset0 = packetBufferPtr + 4;
  packetSize = 0x597e3b; // return address
  (**(code **)(*DAT_01205590 + 0x10))();
  
  // Now pack data pieces into buffer at offset 8, 0xc, 0x10, 0x14
  packetSize = 4;
  (**(code **)(*DAT_01205590 + 0x10))(packetBufferPtr + 8, dataBuffer);  // second chunk data
  (**(code **)(*DAT_01205590 + 0x10))(packetBufferPtr + 0xc, &bufferOffset1, 4); // third chunk
  (**(code **)(*DAT_01205590 + 0x10))(packetBufferPtr + 0x10, &ptrToData2, 4); // fourth chunk
  (**(code **)(*DAT_01205590 + 0x10))(packetBufferPtr + 0x14, &packetSize, 4); // fifth chunk
  
  return 0x18; // total packet size = 24 bytes
}