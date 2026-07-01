// FUNC_NAME: TNLConnection::computePacketChecksum
int __thiscall TNLConnection::computePacketChecksum(int this, int packetId)
{
  // +0x08: pointer to an array of packet structures (size 0x2c each)
  // Each packet structure has a 8-byte header, then 24 bytes of checksummed data (12 ushorts)
  int checksum = 0;
  int packetIndex = getPacketIndex(packetId); // FUN_008bcb50
  if (packetIndex >= 0) {
    int loopCount = 2;
    ushort* currentPtr = (ushort*)(*(int*)(this + 8) + 8 + packetIndex * 0x2c);
    do {
      // Sum 6 consecutive ushorts (offsets -8, -6, -4, -2, 0, +2 bytes relative to currentPtr)
      ushort v0 = currentPtr[-4];  // offset -8
      ushort v1 = currentPtr[-3];  // offset -6
      ushort v2 = currentPtr[-2];  // offset -4
      ushort v3 = currentPtr[-1];  // offset -2
      ushort v4 = currentPtr[0];   // offset  0
      ushort v5 = currentPtr[1];   // offset +2
      checksum += (uint)v0 + (uint)v1 + (uint)v2 + (uint)v3 + (uint)v4 + (uint)v5;
      currentPtr += 6; // advance 12 bytes (6 ushorts)
      loopCount--;
    } while (loopCount != 0);
  }
  return checksum;
}