// FUNC_NAME: NetConnection::processPacket
void __thiscall NetConnection::processPacket(int *packet)
{
  // +0x18: expected packet type identifier
  int expectedType = *(int *)((int)this + 0x18);
  int packetType = *packet;
  
  if (packetType == expectedType) {
    // Process payload (third element of packet structure)
    FUN_00610f90(packet[2]);
    // Post-processing after packet handling
    FUN_00421260();
  }
}