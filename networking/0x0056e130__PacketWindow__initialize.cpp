// FUNC_NAME: PacketWindow::initialize
undefined4 * __thiscall PacketWindow::initialize(undefined4 *this, int *param_2, undefined4 param_3, undefined4 param_4)
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  // Store global pointer to this instance
  DAT_012234e8 = this;
  
  // Store window size (number of slots)
  this[2] = param_3;  // +0x08: windowSize
  
  // Set vtable pointer
  *this = &PTR_FUN_00e3abdc;  // +0x00: vtable
  
  // Store packet buffer pointer
  this[1] = param_2;  // +0x04: packetBuffer
  
  // Call virtual function on packet buffer (likely initialize)
  (**(code **)(*param_2 + 8))();
  
  // Initialize sequence numbers
  this[5] = 0;  // +0x14: nextSendSequence
  this[6] = 0;  // +0x18: nextRecvSequence
  
  // Allocate slot array
  uVar1 = FUN_0056e020();  // allocate memory for slots
  this[3] = uVar1;  // +0x0C: slots
  this[4] = uVar1;  // +0x10: currentSlot
  
  // Initialize linked list of slots (each slot is 0x38 bytes)
  uVar2 = 0;
  this[7] = this[2];  // +0x1C: remainingSlots
  if (this[2] != 0) {
    iVar3 = 0;
    do {
      if (uVar2 != 0) {
        // Link previous slot to this one (prev pointer)
        *(int *)(this[4] + iVar3 + 4) = this[4] + iVar3 + -0x38;
      }
      if (uVar2 < this[2] - 1) {
        // Link this slot to next one (next pointer)
        *(int *)(this[4] + iVar3) = (int)((int *)(this[4] + iVar3) + 0xe);
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0x38;
    } while (uVar2 < (uint)this[2]);
  }
  
  // Clear ACK bitfield (0x400 bytes = 4096 bits = 4096 sequence numbers)
  puVar4 = this + 0xc;  // +0x30: ackBitfield
  for (iVar3 = 0x400; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  
  // Store connection pointer
  this[9] = param_4;  // +0x24: connection
  
  // Create event object for synchronization
  uStack_c = 2;   // event type: manual reset
  uStack_8 = 0x10; // initial state: signaled
  uStack_4 = 0;   // name: null
  uVar1 = (*(code *)**(undefined4 **)this[1])(param_4, &uStack_c);
  this[8] = uVar1;  // +0x20: sendEvent
  
  // Initialize packet window state
  FUN_0056e530();  // resetWindow
  
  return this;
}