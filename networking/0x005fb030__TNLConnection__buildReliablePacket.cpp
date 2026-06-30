// FUNC_NAME: TNLConnection::buildReliablePacket
uint TNLConnection::buildReliablePacket(void)
{
  undefined4 *puVar1;
  int *piVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uint local_10;
  
  puVar1 = *(undefined4 **)(in_EAX + 0x48); // +0x48: mReliableSendList (linked list head)
  puVar5 = (undefined4 *)*puVar1;
  local_10 = 0;
  do {
    if (puVar5 == puVar1) {
      return local_10;
    }
    if (puVar5 == *(undefined4 **)(in_EAX + 0x48)) {
      FUN_00b97aea(); // likely assertion/error handler
    }
    piVar2 = (int *)puVar5[2]; // +0x08: packet data pointer
    iVar3 = (**(code **)(*piVar2 + 8))(); // vtable+8: getPacketSize
    if (*(int *)(iVar3 + 4) != 0) {
      iVar6 = 8 - local_10; // remaining space in 8-byte header
      iVar4 = (**(code **)(*piVar2 + 0xc))(); // vtable+0xc: getPacketDataSize
      if (iVar4 < iVar6) {
        iVar6 = (**(code **)(*piVar2 + 0xc))();
      }
      iVar3 = FUN_006021f0(piVar2 + 4,piVar2,iVar3,piVar2[7],iVar6); // copy packet data
      local_10 = local_10 + iVar3;
    }
    if (puVar5 == *(undefined4 **)(in_EAX + 0x48)) {
      FUN_00b97aea();
    }
    puVar5 = (undefined4 *)*puVar5; // next node in linked list
  } while (local_10 < 8); // max 8 bytes of reliable data per packet
  return local_10;
}