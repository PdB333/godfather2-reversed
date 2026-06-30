// FUNC_NAME: TNLConnection::allocateReliablePacket
void TNLConnection::allocateReliablePacket(int param_1)

{
  uint uVar1;
  int *piVar2;
  undefined4 *puVar3;
  int unaff_EDI;  // this pointer
    
  uVar1 = param_1 + 0x10;
  puVar3 = (undefined4 *)0x0;
  if (uVar1 == 0) {
LAB_00638a50:
    puVar3 = (undefined4 *)0x0;
  }
  else {
    if (uVar1 < 0xfffffffd) {
      puVar3 = (undefined4 *)(*DAT_012059dc)(0,uVar1);  // allocate packet memory
      if (puVar3 == (undefined4 *)0x0) {
        if (unaff_EDI != 0) {
          FUN_00635a80();  // log allocation failure
          return;
        }
        goto LAB_00638a50;
      }
    }
    else {
      FUN_00633920();  // handle invalid size
    }
    if (unaff_EDI != 0) {
      piVar2 = (int *)(*(int *)(unaff_EDI + 0x10) + 0x24);  // +0x10: packet list, +0x24: totalSize counter
      *piVar2 = *piVar2 + uVar1;  // increment total allocated size
    }
  }
  // Initialize packet header
  puVar3[3] = param_1;  // packet data size
  *(undefined1 *)((int)puVar3 + 5) = 2;  // packet type: reliable
  *(undefined1 *)(puVar3 + 1) = 7;  // ping byte
  puVar3[2] = *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x38);  // +0x38: current sequence number
  *puVar3 = *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x10);  // +0x10: linked list next pointer
  *(undefined4 **)(*(int *)(unaff_EDI + 0x10) + 0x10) = puVar3;  // update list head
  return;
}