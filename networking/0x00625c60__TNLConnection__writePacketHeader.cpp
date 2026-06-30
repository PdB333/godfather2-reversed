// FUNC_NAME: TNLConnection::writePacketHeader
void TNLConnection::writePacketHeader(void)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int unaff_ESI;
  
  // Check if the packet sequence number has wrapped around (sequence > ack)
  if (*(uint *)(*(int *)(unaff_ESI + 0x10) + 0x20) <= *(uint *)(*(int *)(unaff_ESI + 0x10) + 0x24))
  {
    // Handle sequence wrap: write ack info for the previous window
    FUN_00627360(); // likely writeAckInfo
  }
  // Get pointer to current write position in packet buffer
  puVar1 = *(undefined4 **)(unaff_ESI + 8);
  // Write packet type (4 = data packet)
  *puVar1 = 4;
  // Get current sequence number
  uVar2 = FUN_00638920(); // likely getNextSequence
  // Write sequence number after type
  puVar1[1] = uVar2;
  // Advance write position by 8 bytes (type + sequence)
  *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + 8;
  return;
}