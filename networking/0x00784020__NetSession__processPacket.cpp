// FUNC_NAME: NetSession::processPacket
void __thiscall NetSession::processPacket(int thisPtr, int packetBuffer, char isReliable)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int local_20;
  undefined4 local_1c;
  int local_18;
  code *pcStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  undefined4 local_8;
  undefined1 *puStack_4;
  
  // +0x68: packet queue count
  if (*(int *)(thisPtr + 0x68) == 0) {
    // +0x74: flags
    if ((*(uint *)(thisPtr + 0x74) >> 3 & 1) == 0) {
      pcStack_14 = FUN_007832c0;  // likely a callback function
      iVar3 = *(int *)(thisPtr + 0x28);  // +0x28: some manager/context pointer
      // Store callback and this pointer at offset 0x26f8
      *(ulonglong *)(iVar3 + 0x26f8) = CONCAT44(FUN_007832c0, thisPtr);
      uStack_c = 0;
      local_10 = 0;
      *(undefined8 *)(iVar3 + 0x2700) = 0;
      puStack_4 = &LAB_00782af0;  // likely a return address label
      local_8 = 0;
      *(undefined8 *)(iVar3 + 0x2708) = 0x782af000000000;
      *(uint *)(thisPtr + 0x74) = *(uint *)(thisPtr + 0x74) | 8;  // set flag bit 3
      local_18 = thisPtr;
    }
    cVar1 = FUN_0043c6c0(*(undefined4 *)(thisPtr + 0x28), DAT_00e52468);  // check if something is initialized
    if (cVar1 == '\0') {
      FUN_0043c490(*(undefined4 *)(thisPtr + 0x28), DAT_00e52468);  // initialize it
    }
  }
  if (packetBuffer == 0) {
    local_20 = 0;
  }
  else {
    local_20 = packetBuffer + 0x48;  // +0x48: packet data offset
  }
  local_1c = 0;
  if (local_20 != 0) {
    local_1c = *(undefined4 *)(local_20 + 4);  // linked list next pointer
    *(int **)(local_20 + 4) = &local_20;  // circular linked list setup
  }
  uVar2 = 0;
  if (*(uint *)(thisPtr + 0x68) != 0) {
    piVar4 = *(int **)(thisPtr + 100);  // +0x64: packet queue array
    do {
      if (*piVar4 == local_20) {
        if (uVar2 != 0xffffffff) goto LAB_0078413c;
        break;
      }
      uVar2 = uVar2 + 1;
      piVar4 = piVar4 + 2;
    } while (uVar2 < *(uint *)(thisPtr + 0x68));
  }
  if (isReliable != '\0') {
    iVar3 = FUN_00471610();  // get some timestamp/sequence
    FUN_007872a0(packetBuffer, iVar3 + 0x30);  // attach sequence number to packet
  }
  FUN_007834e0(&local_20);  // process/queue the packet
LAB_0078413c:
  if ((*(uint *)(thisPtr + 0x74) >> 2 & 1) == 0) {
    if (DAT_0112b36c != 0) {
      FUN_00408900(thisPtr, &DAT_0112b36c, 0x8000);  // send notification/event
    }
    *(uint *)(thisPtr + 0x74) = *(uint *)(thisPtr + 0x74) | 4;  // set flag bit 2
  }
  if (local_20 != 0) {
    FUN_004daf90(&local_20);  // cleanup/free packet data
  }
  return;
}