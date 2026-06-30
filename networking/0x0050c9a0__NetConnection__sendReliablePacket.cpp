// FUNC_NAME: NetConnection::sendReliablePacket
void NetConnection::sendReliablePacket(int param_1, int *param_2)
{
  int iVar1;
  int in_EAX;
  int *piVar2;
  int unaff_FS_OFFSET;
  int local_54;
  undefined1 local_50 [76];
  
  // Check if the packet type is blocked (bit 2 of flags at +0x54)
  if ((*(byte *)(in_EAX * 0x50 + *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x54 + *param_2)
      & 4) == 0) {
    iVar1 = *(int *)(param_1 + 0x24); // +0x24: mConnectionState
    // Check if any of the 4 reliable send slots are occupied (non-zero)
    if (((*(int *)(iVar1 + 0x40) != 0 || *(int *)(iVar1 + 0x44) != 0) ||
        (*(int *)(iVar1 + 0x48) != 0 || *(int *)(iVar1 + 0x4c) != 0)) &&
       ((*(int *)(iVar1 + 0x40) != 0 || *(int *)(iVar1 + 0x44) != 0 ||
        (*(int *)(iVar1 + 0x48) != 0 || *(int *)(iVar1 + 0x4c) != 0)))) {
      piVar2 = (int *)FUN_004e0f60(); // Get packet buffer
      if ((piVar2 != (int *)0x0) && (iVar1 = *piVar2, iVar1 != 0)) {
        if (*(char *)(param_1 + 0x5b) == '\x06') { // +0x5b: mPacketType
          FUN_00510740(param_1,param_2,in_EAX,local_50); // Build reliable packet (type 6)
        }
        else {
          FUN_00510f60(param_1,param_2,in_EAX); // Build other reliable packet
        }
        FUN_004df210(iVar1,local_50,*(undefined4 *)(*(int *)(param_1 + 4) + 0x84),0); // Send packet
        if (local_54 != 0) {
          *(undefined4 *)(local_54 + 8) = 0; // Clear reference
        }
      }
    }
  }
  return;
}