// FUNC_NAME: NetSession::processNextPacket
int NetSession::processNextPacket(int param_1)
{
  int *piVar1;
  int result;
  int packetSize;
  undefined1 buffer [4]; // +0x00: packet buffer
  int packetOffset; // +0x04
  int processedBytes; // +0x08

  packetOffset = 0;
  processedBytes = 0;
  result = FUN_00635ab0(param_1, &LAB_00636660, buffer); // Read next packet from stream
  packetSize = processedBytes;
  if (packetOffset != 0) {
    (*DAT_012059e0)(packetOffset); // Free packet buffer
    piVar1 = (int *)(*(int *)(param_1 + 0x10) + 0x24); // +0x10: stream, +0x24: bytes consumed
    *piVar1 = *piVar1 - packetSize; // Adjust stream position
  }
  packetOffset = 0;
  processedBytes = 0;
  if (result != 0) {
    FUN_006359f0(); // Handle packet processing
  }
  return result;
}