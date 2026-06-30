// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int *this, int packetType, int *outPacket)
{
  uint *puVar1;
  int *in_EAX;
  undefined4 uVar2;
  int iVar3;
  
  if (packetType == 5) {
    // Packet type 5: Reliable data packet
    FUN_00642f70(); // getNextSequence
    if ((*in_EAX == 10) &&
       (((byte)*(undefined4 *)(*(int *)(*this + 0xc) + in_EAX[1] * 4) & 0x3f) == 0x13)) {
      // Check if packet is a valid reliable packet with correct flags
      if (((*outPacket == 0xb) && (this[0xd] <= outPacket[1])) && (outPacket[1] < 0xfa)) {
        this[9] = this[9] + -1; // Decrement retransmit count
      }
      puVar1 = (uint *)(*(int *)(*this + 0xc) + in_EAX[1] * 4);
      *puVar1 = *puVar1 ^ (outPacket[1] << 0xf ^ *puVar1) & 0xff8000;
      *outPacket = *in_EAX;
      outPacket[1] = in_EAX[1];
      return;
    }
    FUN_00642ec0(); // getNextSequence
    if ((*in_EAX == 0xb) && ((this[0xd] <= in_EAX[1] && (in_EAX[1] < 0xfa)))) {
      this[9] = this[9] + -1; // Decrement retransmit count
    }
    if (((*outPacket == 0xb) && (this[0xd] <= outPacket[1])) && (outPacket[1] < 0xfa)) {
      this[9] = this[9] + -1; // Decrement retransmit count
    }
    iVar3 = FUN_006438e0((outPacket[1] << 9 | in_EAX[1]) << 6 | 0x13,*(undefined4 *)(this[3] + 8));
    outPacket[1] = iVar3;
    *outPacket = 10;
    return;
  }
  if (packetType == 0xc) {
    // Packet type 12: Connection request
    FUN_00642b00(); // getConnectionInfo
    FUN_00642880(this); // processConnectionRequest
    *outPacket = *in_EAX;
    outPacket[1] = in_EAX[1];
    outPacket[2] = in_EAX[2];
    outPacket[3] = in_EAX[3];
    return;
  }
  if (packetType != 0xd) {
    // Unknown packet type - forward to default handler
    FUN_00642fc0(); // getDefaultHandler
    uVar2 = FUN_00642fc0(); // getDefaultHandler
    if (((*in_EAX == 0xb) && (this[0xd] <= in_EAX[1])) && (in_EAX[1] < 0xfa)) {
      this[9] = this[9] + -1; // Decrement retransmit count
    }
    if (((*outPacket == 0xb) && (this[0xd] <= outPacket[1])) && (outPacket[1] < 0xfa)) {
      this[9] = this[9] + -1; // Decrement retransmit count
    }
    FUN_00643680(packetType, uVar2); // handleUnknownPacket
    return;
  }
  // Packet type 13: Connection response
  FUN_00642b00(); // getConnectionInfo
  FUN_00642880(this); // processConnectionResponse
  *outPacket = *in_EAX;
  outPacket[1] = in_EAX[1];
  outPacket[2] = in_EAX[2];
  outPacket[4] = in_EAX[4];
  return;
}