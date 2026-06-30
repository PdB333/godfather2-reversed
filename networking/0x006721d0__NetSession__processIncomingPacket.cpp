// FUNC_NAME: NetSession::processIncomingPacket
int NetSession::processIncomingPacket(int param_1, int param_2)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  uint local_4;
  
  iVar4 = param_2 * 0xc;
  iVar1 = *(int *)(iVar4 + 4 + *(int *)(param_1 + 4)); // +0x4: packet buffer pointer
  local_10 = 0;
  local_4 = 0;
  local_8 = 0;
  iVar2 = FUN_006761b0(); // checkConnectionState
  if (iVar2 == 0) {
    iVar2 = FUN_00676150(); // checkSessionActive
    if (iVar2 == 0) {
      return 0x4e24; // error code: session not active
    }
    local_c = 3; // packet type: reliable
  }
  else {
    local_c = 2; // packet type: unreliable
  }
  *(short *)(iVar4 + *(int *)(param_1 + 4)) = (short)local_c; // store packet type
  if ((short)local_c == 1) {
    local_8 = *(undefined4 *)(iVar4 + 8 + *(int *)(param_1 + 4)); // +0x8: sequence number for reliable
  }
  iVar4 = 0;
  do {
    *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(iVar1 + 0xc); // copy next packet header
    uVar3 = FUN_00675810(local_c,iVar4,iVar1,local_8,0,&local_10); // decodePacket
    if ((local_10 == 0) && (iVar2 = FUN_00673280(uVar3), local_10 == 0)) { // validatePacket
      local_4 = (uint)*(ushort *)(iVar2 + 0x58); // +0x58: packet payload size
      local_10 = FUN_00671cd0(param_1,param_2,iVar4); // processPacketData
      FUN_00674eb0(); // updateAckState
      if ((local_10 == 0) && (FUN_00675d20(), local_10 == 0)) { // checkResendQueue
        local_10 = FUN_00671e60(param_1,*(ushort *)(param_1 + 8) - 1); // processNextPacket
      }
    }
    iVar4 = iVar4 + 1;
  } while ((iVar4 < (int)local_4) && (local_10 == 0));
  return local_10;
}