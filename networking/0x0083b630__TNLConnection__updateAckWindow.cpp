// FUNC_NAME: TNLConnection::updateAckWindow
void __thiscall TNLConnection::updateAckWindow(int thisPtr, int ackIndex, int windowSize)
{
  byte shiftAmount;
  int i;
  ushort ackMask;
  uint fullMask;
  
  fullMask = 0;
  ackMask = 0;
  i = 0;
  if (0 < windowSize) {
    do {
      shiftAmount = (byte)i;
      i = i + 1;
      fullMask = fullMask | 1 << (shiftAmount & 0x1f);
      ackMask = (ushort)fullMask;
    } while (i < windowSize);
  }
  // Check if all slots in window are acknowledged (mask matches)
  if (ackMask == (*(ushort *)(thisPtr + 0x1e) & ackMask)) {
    *(undefined2 *)(thisPtr + 0x1e) = 0;  // +0x1e: ackWindowMask (16-bit)
  }
  // Find next unacknowledged slot starting from ackIndex
  if (((uint)*(ushort *)(thisPtr + 0x1e) & 1 << ((byte)ackIndex & 0x1f)) != 0) {
    do {
      ackIndex = (ackIndex + 1) % windowSize;
    } while (((uint)*(ushort *)(thisPtr + 0x1e) & 1 << ((byte)ackIndex & 0x1f)) != 0);
  }
  return;
}