// FUNC_NAME: TNLConnection::removeFromSendQueue
void __fastcall TNLConnection::removeFromSendQueue(int this)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *local_4;
  
  iVar1 = *(int *)(this + 0x54); // +0x54: sendQueueCount
  if (iVar1 != 0) {
    local_4 = (undefined4 *)(this + 0x30 + iVar1 * 4); // +0x30: sendQueue array start
    iVar2 = iVar1;
    do {
      iVar2 = iVar2 + -1;
      *(int *)(this + 0x54) = *(int *)(this + 0x54) + -1; // decrement sendQueueCount
      if (iVar2 != *(int *)(this + 0x54)) {
        *local_4 = *(undefined4 *)(this + 0x34 + *(int *)(this + 0x54) * 4); // shift last element into removed slot
      }
      // Check if all queues are empty: sendQueueCount + ackQueueCount + recvQueueCount + unsentQueueCount == 0
      if (*(int *)(this + 0x78) + *(int *)(this + 0x9c) + *(int *)(this + 0x54) +
          *(int *)(this + 0x30) == 0) {
        uVar3 = 0;
        *(undefined4 *)(this + 0xa0) = 0; // +0xa0: some flag
        if (*(int *)(this + 0xdc) != 0) { // +0xdc: callbackCount
          do {
            (**(code **)(**(int **)(*(int *)(this + 0xd8) + uVar3 * 4) + 4))(); // call each callback
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(uint *)(this + 0xdc));
        }
      }
      local_4 = local_4 + -1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}