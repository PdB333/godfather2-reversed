// FUNC_NAME: TNLConnection::processPacketHeader
bool __thiscall TNLConnection::processPacketHeader(int thisPtr, undefined4 *outPacket, int packetType)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 in_EAX;
  undefined4 uVar3;
  bool bVar4;
  byte local_c [8];
  undefined4 uStack_4;
  
  puVar2 = outPacket;
  FUN_004af8c0(local_c,0x800); // Check for incoming data availability
  if ((local_c[0] & 1) != 0) {
    uVar3 = FUN_005565f0(); // Get sequence number
    outPacket = (undefined4 *)0x0;
    (**(code **)(*(int *)*puVar2 + 0x98))(&outPacket,uVar3); // Virtual call to packet handler
    iVar1 = *(int *)(thisPtr + 0x10); // +0x10: connection state
    puVar2[8] = iVar1; // Store connection state in packet
    if (*(short *)(iVar1 + 4) != 0) { // +0x04: packet count
      *(short *)(iVar1 + 6) = *(short *)(iVar1 + 6) + 1; // +0x06: packet counter
    }
    puVar2[9] = uStack_4; // Store stack value
    return true;
  }
  if (packetType == 3) {
    FUN_00558520(thisPtr); // Handle packet type 3
    return true;
  }
  if (packetType == 4) {
    FUN_005585a0(puVar2,thisPtr,in_EAX); // Handle packet type 4
    return true;
  }
  bVar4 = packetType == 2;
  if (bVar4) {
    FUN_00558660(puVar2,thisPtr,in_EAX); // Handle packet type 2
  }
  return bVar4;
}