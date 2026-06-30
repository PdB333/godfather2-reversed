// FUNC_NAME: NetSession::processOutgoingPacketQueue
void __thiscall NetSession::processOutgoingPacketQueue(uint *this, undefined4 param_2, undefined4 param_3, int param_4)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint *local_94;
  byte local_90 [128]; // stack buffer for packet list operations
  int local_10;
  
  // Get pointer to active connection list from session +0x60
  local_94 = *(uint **)(*(int *)*this + 0x60);
  iVar4 = 0;
  local_10 = 0;
  if (local_94 != (uint *)0x0) {
    do {
      // Check if packet is eligible for sending: bit 0xF must be clear (not acked) and connection is not blocked
      if (((~(byte)(*local_94 >> 0xf) & 1) == 0) && (cVar1 = FUN_005a4140(), cVar1 == '\\0')) {
        // // Check if packet has pending reliable data (signed flag at +0x58)
        if (*(int *)local_94[0x16] < 0) {
          // Process existing out-of-order packets: reorder using customer ordering (FUN_005b3470 returns sorted list)
          while ((0 < iVar4 &&
                 (iVar2 = FUN_005b3470(local_90), **(int **)(iVar2 + 0x58) < (int)local_94[0xc]))) {
            param_4 = param_4 + -1;
            uVar3 = FUN_005b3470(local_90);
            // Mark packet as sent (0xFFFFFFFF = invalid seq)
            FUN_005b5480(uVar3,param_2,0xffffffff,param_4);
            FUN_005b3390(local_90);
            iVar4 = local_10;
          }
          // Send the current packet
          FUN_005b5480(local_94,param_2,param_3,param_4);
        }
        else {
          // Packet has no pending reliable data, initialize retransmit and send immediately
          FUN_005b3280(local_94);
          // Send with sequence number = 1 (new packet)
          FUN_005b5480(local_94,param_2,1,param_4);
          param_4 = param_4 + 1;
          iVar4 = local_10;
        }
      }
      local_94 = (uint *)local_94[0x18]; // +0x60: next packet in linked list
    } while (local_94 != (uint *)0x0);
    // Flush remaining reordered packets
    while (0 < iVar4) {
      param_4 = param_4 + -1;
      uVar3 = FUN_005b3470(local_90);
      FUN_005b5480(uVar3,param_2,0xffffffff,param_4);
      FUN_005b3390(local_90);
      iVar4 = local_10;
    }
  }
  // Finalize transmission (e.g., flush network buffer)
  FUN_005b31e0();
  return;
}