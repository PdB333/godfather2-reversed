// FUNC_NAME: TNLConnection::writeReliablePacket

undefined4 TNLConnection::writeReliablePacket(int this_)
{
  int *packetType;
  undefined4 sequenceNum;
  uint newWritePos;
  int *extraout_ECX;
  int *readPtr;
  int extraout_EDX;
  int diff;

  packetType = *(int **)(this_ + 0x10); // +0x10: pointer to current packet header type
  // Assertion: read pointer (this_+0x0c) must not exceed write pointer (this_+0x10) and packet type must be 5
  if (((*(int **)(this_ + 0x0c) <= packetType) || (packetType == (int *)0x0)) || (*packetType != 5)) {
    FUN_00627ac0(PTR_s_table_00e2a8b0);
  }
  sequenceNum = FUN_00628820(1); // Get next sequence number

  // Check capacity: available space in packet list (in 8-byte slots) + 0x28 must be less than 0x4001
  if ((*(int *)(this_ + 0x0c) - *(int *)(this_ + 0x10) >> 3) + 0x28 < 0x4001) {
    // Check if remaining buffer space is less than 0x141 bytes
    if (*(int *)(this_ + 0x1c) - *(int *)(this_ + 0x0c) < 0x141) {
      FUN_00635c70(); // Expand buffer
    }
    newWritePos = *(int *)(this_ + 0x0c) + 0x140; // Reserve 320 bytes for packet data
    if (*(uint *)(*(int *)(this_ + 0x18) + 4) < newWritePos) {
      *(uint *)(*(int *)(this_ + 0x18) + 4) = newWritePos; // Update buffer size
    }
    diff = *(int *)(this_ + 0x10);
    readPtr = *(int **)(this_ + 0x0c);
    packetType = (int *)(diff + 8);
    // Validate next packet type in the queue
    if ((((readPtr <= packetType) || (packetType == (int *)0x0)) || (*packetType < 1)) ||
       (((packetType < readPtr && (packetType != (int *)0x0)) && (*packetType == 6)))) goto LAB_00630a9f;
    sequenceNum = 2;
    FUN_00627ac0(PTR_s_function_00e2a8b4);
  }
  FUN_00627bd0("stack overflow (%s)",&DAT_00e2f044);
  readPtr = extraout_ECX;
  diff = extraout_EDX;
LAB_00630a9f:
  // Zero out packet entries from current write pointer up to readPointer + 0x10
  if (readPtr < (int *)(diff + 0x10)) {
    do {
      **(undefined4 **)(this_ + 0x0c) = 0;
      *(int *)(this_ + 0x0c) = *(int *)(this_ + 0x0c) + 8;
    } while (*(uint *)(this_ + 0x0c) < *(int *)(this_ + 0x10) + 0x10U);
  }
  *(int *)(this_ + 0x0c) = *(int *)(this_ + 0x10) + 0x10; // Reset write pointer to after the first packet
  FUN_006306c0(this_, 1, sequenceNum); // Finalize and transmit
  return 0;
}