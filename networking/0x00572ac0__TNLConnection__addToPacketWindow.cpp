// FUNC_NAME: TNLConnection::addToPacketWindow
void __fastcall TNLConnection::addToPacketWindow(void *this, undefined8 *param_1)
{
  ushort *puVar1;
  int in_EAX;
  undefined8 *puVar2;
  
  // Check if the packet is for the send window or the receive window based on some flag
  if (*(short *)((int)this + 0xc) == 0) {
    // Send window: check if we have room in the send window (size at +0xac, count at +0xa8)
    if ((int)*(short *)(in_EAX + 0xa8) < *(short *)(in_EAX + 0xac) + -1) {
      puVar2 = (undefined8 *)(*(short *)(in_EAX + 0xa8) * 0x20 + *(int *)(in_EAX + 0xa0));
      *puVar2 = *param_1;
      puVar2[1] = param_1[1];
      puVar2[2] = param_1[2];
      puVar2[3] = param_1[3];
      puVar1 = (ushort *)(*(short *)(in_EAX + 0xa8) * 0x20 + 6 + *(int *)(in_EAX + 0xa0));
      *puVar1 = *puVar1 | 0x80; // Mark packet as active/valid
      *(short *)(in_EAX + 0xa8) = *(short *)(in_EAX + 0xa8) + 1; // Increment send window count
      FUN_00572a00(*(undefined4 *)(in_EAX + 0xa0),(int)*(short *)(in_EAX + 0xa8)); // Notify window updated
      return;
    }
  }
  else if (*(short *)(in_EAX + 0xaa) < 0x45) { // Receive window: max 69 packets
    puVar2 = (undefined8 *)(*(short *)(in_EAX + 0xaa) * 0x20 + *(int *)(in_EAX + 0xa4));
    *puVar2 = *param_1;
    puVar2[1] = param_1[1];
    puVar2[2] = param_1[2];
    puVar2[3] = param_1[3];
    puVar1 = (ushort *)(*(short *)(in_EAX + 0xaa) * 0x20 + 6 + *(int *)(in_EAX + 0xa4));
    *puVar1 = *puVar1 | 0x80; // Mark packet as active/valid
    *(short *)(in_EAX + 0xaa) = *(short *)(in_EAX + 0xaa) + 1; // Increment receive window count
    FUN_00572a00(*(undefined4 *)(in_EAX + 0xa4),(int)*(short *)(in_EAX + 0xaa)); // Notify window updated
  }
  return;
}