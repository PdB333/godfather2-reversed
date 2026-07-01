// FUNC_NAME: NetSession::processPacket
void NetSession::processPacket(void)
{
  int *piVar1;
  uint *in_EAX; // this pointer (NetSession*)
  
  piVar1 = (int *)*DAT_0119caec; // g_pendingPacketList or similar global list head
  do {
    if (piVar1 == (int *)0x0) {
LAB_005aa340:
      if (1 < *(ushort *)((int)in_EAX + 2)) { // +0x02: packetSequenceCount or similar
        FUN_005aa3d0(); // processReliablePacket
        FUN_005b2380(); // processAckPacket
        *in_EAX = *in_EAX & 0xffff7fff; // clear bit 15 (maybe a flag)
        (**(code **)(&DAT_0103aee0 + (*in_EAX & 0x7fff) * 4))(); // dispatch via function table
        return;
      }
      if (*(ushort *)((int)in_EAX + 2) != 1) {
        FUN_0059bf00(); // handleUnreliablePacket
      }
      (**(code **)(&DAT_0103aee0 + (*in_EAX & 0x7fff) * 4))(); // dispatch via function table
      return;
    }
    if (*(uint **)(*piVar1 + 8) == in_EAX) { // check if packet belongs to this session
      FUN_005a2d20(DAT_0119caec); // removeFromPendingList
      goto LAB_005aa340;
    }
    piVar1 = (int *)piVar1[1]; // next node
  } while( true );
}