// FUNC_NAME: TNLConnection::sendPacketTo
undefined4 __thiscall TNLConnection::sendPacketTo(int thisPtr, undefined4 address, undefined4 packetData)
{
  int *listHead;
  undefined4 result;
  int *currentNode;
  uint nodeCount;
  
  currentNode = *(int **)(thisPtr + 0x34);
  listHead = (int *)(thisPtr + 0x34);
  nodeCount = 0;
  if (currentNode != listHead) {
    do {
      currentNode = (int *)*currentNode;
      nodeCount = nodeCount + 1;
    } while (currentNode != listHead);
    if (9 < nodeCount) {
      return 0;
    }
  }
  result = FUN_008a09a0(listHead, address,
                       -(uint)(*(int *)(thisPtr + 0xc4) != 0) & 0x80000000 |
                       *(uint *)(thisPtr + 0xc0), packetData);
  DAT_00d58cbc = *(int *)(thisPtr + 0xcc); // likely sending timestamp or packet number
  *(int *)(thisPtr + 0xc0) = *(int *)(thisPtr + 0xc0) + 1; // increment sequence counter
  *(undefined4 *)(thisPtr + 0xcc) = DAT_00d58cbc;
  return result;
}