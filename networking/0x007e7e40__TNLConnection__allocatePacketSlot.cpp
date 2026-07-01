// FUNC_NAME: TNLConnection::allocatePacketSlot
void __thiscall TNLConnection::allocatePacketSlot(int this, uint sequenceId)
{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *local_10;
  uint local_c;
  uint *local_8;
  int local_4;
  
  puVar5 = (uint *)0x0;
  puVar6 = (uint *)0x0;
  local_8 = (uint *)0x0;
  local_10 = (uint *)0x0;
  uVar4 = 0;
  local_c = 0;
  local_4 = 0;
  puVar2 = (uint *)(this + 0x590); // +0x590: packetSlots array start (32 slots, 0x1E bytes each)
  do {
    puVar3 = local_8;
    if (local_8 != (uint *)0x0) goto LAB_007e8044;
    puVar3 = puVar2 + -5;
    if (puVar2[-5] == sequenceId) goto LAB_007e8044; // slot[0].sequenceId match
    if (puVar2[-5] == 0) { // empty slot
      if (local_10 == (uint *)0x0) {
        local_10 = puVar3; // first empty slot candidate
      }
    }
    else if (puVar2[-1] < DAT_01205224) { // slot[4].sendTime < currentTime
      if ((puVar5 == (uint *)0x0) || (*puVar2 < local_c)) { // slot[5].ackTime < bestAckTime
        local_c = *puVar2;
        puVar5 = puVar3; // oldest unacknowledged slot
      }
    }
    else if ((puVar6 == (uint *)0x0) || (*puVar2 < uVar4)) {
      uVar4 = *puVar2;
      puVar6 = puVar3; // oldest acknowledged slot
    }
    puVar3 = puVar2 + 1;
    if (puVar2[1] == sequenceId) goto LAB_007e8044; // slot[1].sequenceId
    if (puVar2[1] == 0) {
      if (local_10 == (uint *)0x0) {
        local_10 = puVar3;
      }
    }
    else if (puVar2[5] < DAT_01205224) { // slot[9].sendTime
      if ((puVar5 == (uint *)0x0) || (puVar2[6] < local_c)) { // slot[10].ackTime
        local_c = puVar2[6];
        puVar5 = puVar3;
      }
    }
    else if ((puVar6 == (uint *)0x0) || (puVar2[6] < uVar4)) {
      uVar4 = puVar2[6];
      puVar6 = puVar3;
    }
    puVar3 = puVar2 + 7;
    if (puVar2[7] == sequenceId) goto LAB_007e8044; // slot[7].sequenceId
    if (puVar2[7] == 0) {
      if (local_10 == (uint *)0x0) {
        local_10 = puVar3;
      }
    }
    else if (puVar2[0xb] < DAT_01205224) { // slot[11].sendTime
      if ((puVar5 == (uint *)0x0) || (puVar2[0xc] < local_c)) { // slot[12].ackTime
        local_c = puVar2[0xc];
        puVar5 = puVar3;
      }
    }
    else if ((puVar6 == (uint *)0x0) || (puVar2[0xc] < uVar4)) {
      uVar4 = puVar2[0xc];
      puVar6 = puVar3;
    }
    puVar3 = puVar2 + 0xd;
    if (puVar2[0xd] == sequenceId) goto LAB_007e8044; // slot[13].sequenceId
    if (puVar2[0xd] == 0) {
      if (local_10 == (uint *)0x0) {
        local_10 = puVar3;
      }
    }
    else if (puVar2[0x11] < DAT_01205224) { // slot[17].sendTime
      if ((puVar5 == (uint *)0x0) || (puVar2[0x12] < local_c)) { // slot[18].ackTime
        local_c = puVar2[0x12];
        puVar5 = puVar3;
      }
    }
    else if ((puVar6 == (uint *)0x0) || (puVar2[0x12] < uVar4)) {
      uVar4 = puVar2[0x12];
      puVar6 = puVar3;
    }
    puVar3 = puVar2 + 0x13;
    puVar1 = puVar3;
    if (puVar2[0x13] != sequenceId) { // slot[19].sequenceId
      puVar1 = local_8;
      if (puVar2[0x13] == 0) {
        if (local_10 == (uint *)0x0) {
          local_10 = puVar3;
        }
      }
      else if (puVar2[0x17] < DAT_01205224) { // slot[23].sendTime
        if ((puVar5 == (uint *)0x0) || (puVar2[0x18] < local_c)) { // slot[24].ackTime
          local_c = puVar2[0x18];
          puVar5 = puVar3;
        }
      }
      else if ((puVar6 == (uint *)0x0) || (puVar2[0x18] < uVar4)) {
        uVar4 = puVar2[0x18];
        puVar6 = puVar3;
      }
    }
    local_8 = puVar1;
    local_4 = local_4 + 5;
    puVar2 = puVar2 + 0x1e; // advance to next slot (30 bytes per slot)
  } while (local_4 < 0x14); // 20 iterations = 5 slots per iteration * 4 = 20 slots? Actually 5*4=20, but we have 32 slots. The loop processes 5 slots per iteration, 4 iterations = 20 slots. This is likely a bug or the array is 20 slots.
  puVar3 = local_8;
  if ((local_8 == (uint *)0x0) && (puVar3 = local_10, local_10 == (uint *)0x0)) {
    if (puVar5 == (uint *)0x0) {
      puVar6[3] = 0; // clear slot[3] (flags?)
      puVar3 = puVar6;
    }
    else {
      puVar5[3] = 0;
      puVar3 = puVar5;
    }
  }
LAB_007e8044:
  if (puVar3 != (uint *)0x0) {
    *puVar3 = sequenceId; // assign sequence ID to slot
  }
  return;
}