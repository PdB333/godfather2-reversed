// FUNC_NAME: NetSession::processIncomingPacket
void __fastcall NetSession::processIncomingPacket(int *thisPtr)
{
  int *listNode;
  char hasData;
  undefined4 packetData;
  int *newNode;
  int nodeValue;
  int *localListHead;
  
  // Check if any of the 4 packet slots (offset 0xC4E, 0xC4F, 0xC50, 0xC51) have data
  if ((((thisPtr[0xc4e] != 0) || (thisPtr[0xc4f] != 0)) || (thisPtr[0xc50] != 0)) ||
     (thisPtr[0xc51] != 0)) {
    localListHead = thisPtr;
    FUN_009ae900(1); // likely lock or enter critical section
    listNode = thisPtr + 0xc52; // +0xC52: current packet list head pointer
    if (thisPtr[0xc52] != 0) {
      FUN_004df600(); // free list or cleanup
    }
    // Call virtual function at vtable+0x58 to get packet data
    packetData = (**(code **)(*thisPtr + 0x58))(0, thisPtr, 0, 0);
    packetData = FUN_00471610(packetData); // decode/transform packet
    // Insert packet into list at offset 0xC4E
    newNode = (int *)FUN_004df330(&localListHead, thisPtr + 0xc4e, packetData);
    if (*listNode != 0) {
      *(undefined4 *)(*listNode + 8) = 0; // clear next pointer
      *listNode = 0;
    }
    nodeValue = *newNode;
    *listNode = nodeValue;
    if (nodeValue != 0) {
      *(int **)(nodeValue + 8) = listNode; // set previous pointer
      *newNode = 0;
    }
    if (localListHead != (int *)0x0) {
      localListHead[2] = 0; // clear tail pointer
    }
    hasData = FUN_00481660(); // check if more data available
    if (hasData != '\0') {
      nodeValue = FUN_009c8e50(0x38); // allocate memory (0x38 bytes)
      if (nodeValue == 0) {
        packetData = 0;
      }
      else {
        packetData = FUN_007a0800(thisPtr); // create packet object
      }
      FUN_00481690(packetData); // queue packet for processing
    }
    hasData = FUN_00481620(); // check for pending events
    if (hasData != '\0') {
      FUN_00440590(&DAT_0112b90c, thisPtr + 0xf, thisPtr[0xc4d], 0, 4); // send event notification
    }
  }
  return;
}