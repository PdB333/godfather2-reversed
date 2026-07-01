// FUNC_NAME: NetConnection::sendPacketCheckpoint
void __thiscall sendPacketCheckpoint(int this, char isAck)
{
  undefined1 *nullTerminatedPrevCheck;
  undefined1 *local_10 [3];
  code *freeFunc;
  
  FUN_004d4a60(local_10,1,"%04X.%04X",*(undefined2 *)(*(int *)(this + 0x1c) + 0x70),
               *(undefined2 *)(*(int *)(this + 0x1c) + 0x74));
  nullTerminatedPrevCheck = local_10[0];
  if (local_10[0] == (undefined1 *)0x0) {
    nullTerminatedPrevCheck = &DAT_0120546e;
  }
  FUN_009085a0(0x53504750,0x43484b52,nullTerminatedPrevCheck);
  *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 1;
  if (isAck == '\0') {
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) & 0xfffffffd;
  }
  else {
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 2;
  }
  FUN_004511c0();
  FUN_008fbfe0();
  if (local_10[0] != (undefined1 *)0x0) {
    (*freeFunc)(local_10[0]);
  }
  return;
}