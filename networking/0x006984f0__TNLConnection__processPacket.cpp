// FUNC_NAME: TNLConnection::processPacket
void TNLConnection::processPacket(void)
{
  // in_EAX points to this (TNLConnection*)
  // unaff_ESI points to packet data buffer
  // +0x04: packetSequence (int)
  // +0x00: connectionId (int)
  
  if (*(int*)(unaff_ESI + 1) == 0) {  // packetSequence == 0
    FUN_004dba00(*in_EAX, in_EAX[1]);  // handleAck(connectionId, sequence)
    return;
  }
  
  FUN_004dbf70(*in_EAX, in_EAX[1], &DAT_00e36ef4, 1);  // processReliablePacket(connectionId, sequence, data, 1)
  FUN_004dbf70(local_10, local_c, *unaff_ESI, unaff_ESI[1]);  // processReliablePacket(..., packetData, packetSize)
  
  if (local_10 != 0) {
    (*local_4)(local_10);  // call packet handler
  }
  
  FUN_004dd3c0();  // updatePacketWindow()
  FUN_004dba00(local_20, uStack_1c);  // handleAck(connectionId, sequence)
  
  if (local_20 != 0) {
    (*pcStack_14)(local_20);  // call ack handler
  }
}