// FUNC_NAME: TNLConnection::processPacketHeader
void __thiscall TNLConnection::processPacketHeader(uint param_1)
{
  uint in_EAX;
  undefined4 uVar1;
  int unaff_ESI;
  undefined4 *in_stack_00000010;
  
  *in_stack_00000010 = 0;
  *(uint *)(*(int *)(unaff_ESI + 0x180) + 0x9c) = param_1 & 0x80; // +0x9c: packetFlags
  *(uint *)(*(int *)(unaff_ESI + 0x180) + 0xa4) = in_EAX & 0xff; // +0xa4: sequenceNumber
  if (((*(int *)(unaff_ESI + 0x24) == 0) || (*(int *)(unaff_ESI + 0x40) != 0)) ||
     ((param_1 & 0x100) != 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined4 *)(unaff_ESI + 0x28) = uVar1; // +0x28: bReliablePending
  *(uint *)(unaff_ESI + 0x2c) = ~(param_1 >> 8 & 0xff) & 1; // +0x2c: bAckPending
  *(undefined4 *)(unaff_ESI + 0x120) = 0; // +0x120: currentPacketTime
  FUN_00673b60(); // likely buildReliablePacket
  *(undefined4 *)(unaff_ESI + 0xcc) = 1; // +0xcc: bPacketInFlight
  *(undefined4 *)(unaff_ESI + 0xe8) = 0; // +0xe8: retransmitCount
  if (*(code **)(unaff_ESI + 0x40) != (code *)0x0) {
    (**(code **)(unaff_ESI + 0x40))(); // callback at +0x40
  }
  return;
}