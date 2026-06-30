// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int thisPtr, int *outPacket, float *packetData)
{
  ushort uVar1;
  int packetIndex;
  char bVar3;
  int iVar4;
  float10 fVar5;
  int local_44;
  int local_40;
  undefined **local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined8 local_2c;
  undefined8 local_24;
  undefined8 local_1c;
  undefined8 local_14;
  undefined4 local_c;
  
  // Check if packet sequence number is within the receive window
  // +0x3c: mHighestReceivedSeq, +0x90: mReceiveWindowBase
  if ((int)(uint)*(ushort *)(packetData + 3) <
      (int)((uint)*(ushort *)(thisPtr + 0x3c) - (uint)*(ushort *)(thisPtr + 0x90))) {
    packetIndex = FUN_005fcd80((uint)*(ushort *)(packetData + 3)); // getPacketSlot
  }
  else {
    // Check if packet has already been processed (bit 0x4000 in flags)
    if (((*(ushort *)((int)packetData + 10) & 0x4000) != 0) || 
        (packetIndex = FUN_005fcde0(), packetIndex == 0)) // allocatePacketSlot
    goto LAB_005fd324;
    
    // Check if this is a reliable packet (bit 0x2000 in flags)
    if ((*(ushort *)((int)packetData + 10) & 0x2000) != 0) {
      // Copy packet data from the packet buffer
      // +0x20: mPacketBuffer (array of 0x24 byte entries)
      local_2c = *(undefined8 *)
                  (*(int *)(thisPtr + 0x20) + (uint)*(ushort *)((int)packetData + 6) * 0x24);
      iVar2 = *(int *)(thisPtr + 0x20) + (uint)*(ushort *)((int)packetData + 6) * 0x24;
      local_24 = *(undefined8 *)(iVar2 + 8);
      local_1c = *(undefined8 *)(iVar2 + 0x10);
      local_14 = *(undefined8 *)(iVar2 + 0x18);
      local_c = *(undefined4 *)(iVar2 + 0x20);
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_3c = &PTR_LAB_00e4081c;
      local_44 = packetIndex;
      FUN_00602490(&local_2c, &local_3c, DAT_00e2eb58); // decompressPacket
      bVar3 = FUN_005f5cb0(&local_44, &local_40); // validatePacketChecksum
      packetIndex = local_44;
      if (bVar3 == '\0') {
        // Mark packet as processed (set bit 0x4000)
        *(ushort *)((int)packetData + 10) = *(ushort *)((int)packetData + 10) | 0x4000;
      }
      else {
        // Calculate distance between packet positions
        fVar5 = (float10)FUN_0045c4b0(&local_2c, local_40); // calculateDistance
        *packetData = (float)fVar5;
        local_40 = local_40 - *(int *)(packetIndex + 0x20);
        // Calculate relative packet index
        *(short *)(packetData + 1) =
             ((short)(local_40 / 0x24) + (short)(local_40 >> 0x1f)) -
             (short)((longlong)local_40 * 0x38e38e39 >> 0x3f);
      }
      // Clear reliable flag (bit 0x2000)
      *(ushort *)((int)packetData + 10) = *(ushort *)((int)packetData + 10) & 0xdfff;
      FUN_005fc970(); // releasePacketSlot
    }
  }
  
  if (packetIndex != 0) {
    uVar1 = *(ushort *)(packetData + 1);
    iVar2 = *(int *)(packetIndex + 0x20);
    outPacket[1] = 0;
    *outPacket = packetIndex;
    outPacket[1] = *(int *)(packetIndex + 4);
    *(int **)(packetIndex + 4) = outPacket;
    outPacket[2] = iVar2 + (uint)uVar1 * 0x24;
    return;
  }
  
LAB_005fd324:
  *outPacket = 0;
  outPacket[1] = 0;
  outPacket[2] = 0;
  return;
}