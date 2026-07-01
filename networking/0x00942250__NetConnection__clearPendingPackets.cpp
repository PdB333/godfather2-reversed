// FUNC_NAME: NetConnection::clearPendingPackets
void __fastcall NetConnection::clearPendingPackets(undefined4 *this)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int local_4;
  int *piVar5;
  
  // Check if there's a pending reliable packet (offset +0x2018 = 0x806*4)
  if (this[0x806] != 0) {
    FUN_00422770(0);
  }
  // Clear the connection state
  FUN_004346d0(*this);
  // Mark no pending reliable packet
  this[0x806] = 0;
  // Clear the send and receive packet queues (offsets +0x2010 and +0x2014)
  FUN_006065a0(this[0x804],0);
  FUN_006065a0(this[0x805],0);
  piVar3 = this + 0x804;
  local_4 = 0x3f;
  piVar4 = this + 0x81e;
  do {
    piVar5 = piVar4 + -0x20;
    piVar3 = piVar3 + -0x20;
    // Check if the packet slot has valid magic numbers (indicating an active packet)
    if (((((piVar4[-0x22] != -0x45245246) || (piVar4[-0x21] != -0x41104111)) ||
         (*piVar5 != -0x153ea5ab)) || (piVar4[-0x1f] != -0x6eeff6ef)) &&
       (iVar1 = *piVar3, iVar1 != 0)) {
      // Packet slot is active - free it
      FUN_004bfcf0();
      piVar2 = (int *)FUN_009c8f80();
      (**(code **)(*piVar2 + 4))(iVar1,0xa0);
    }
    local_4 = local_4 + -1;
    // Clear the packet slot data (magic numbers and pointer)
    *piVar3 = 0;
    piVar4[-0x1f] = 0;
    *piVar5 = 0;
    piVar4[-0x21] = 0;
    piVar4[-0x22] = 0;
    piVar4 = piVar5;
  } while (-1 < local_4);
  return;
}