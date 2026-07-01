// FUNC_NAME: TNLConnection::addToSendQueue
void __thiscall TNLConnection::addToSendQueue(int this, undefined4 packetData)
{
  // +0x10c: sendQueueCount (uint, max 0x20 = 32 slots)
  // +0x88: sendQueue array (each slot 4 bytes, holds packet data)
  if (*(uint *)(this + 0x10c) < 0x20) {
    *(undefined4 *)(this + 0x88 + *(uint *)(this + 0x10c) * 4) = packetData;
    *(int *)(this + 0x10c) = *(int *)(this + 0x10c) + 1;
  }
  return;
}