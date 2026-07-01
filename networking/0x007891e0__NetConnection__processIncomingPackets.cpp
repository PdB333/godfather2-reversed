// FUNC_NAME: NetConnection::processIncomingPackets
void __thiscall NetConnection::processIncomingPackets(int *this, int *packetQueue)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 *puVar6;
  float fVar7;
  
  iVar3 = *packetQueue;
  while (iVar3 != 0) {
    puVar6 = (undefined4 *)*packetQueue;
    FUN_00788b40(puVar6); // likely packet::decode or similar
    iVar3 = FUN_007856f0(puVar6[1]); // get sequence number info
    if (*this == 0) {
      fVar7 = *(float *)(iVar3 + 8); // +0x08: timeDelta or rtt
    }
    else {
      fVar7 = *(float *)(iVar3 + 0xc); // +0x0C: alternate timeDelta
    }
    this[7] = (int)((float)this[7] + fVar7); // +0x1C: accumulatedTime
    this[8] = (int)(*(float *)(iVar3 + 0x10) + (float)this[8]); // +0x20: accumulatedTime2
    *puVar6 = 0;
    if ((undefined4 *)this[1] == (undefined4 *)0x0) {
      *this = (int)puVar6; // +0x00: head of free list
    }
    else {
      *(undefined4 *)this[1] = puVar6; // +0x04: tail of free list
    }
    this[1] = (int)puVar6;
    iVar3 = *packetQueue;
  }
  uVar4 = FUN_007857f0(); // get current time
  if ((uint)this[10] < uVar4) { // +0x28: lastProcessedTime
    iVar3 = (this[10] - uVar4) + packetQueue[10]; // +0x28: timeBudget
    if (iVar3 != 0) {
      piVar1 = (int *)packetQueue[3]; // +0x0C: pendingPackets
      for (; (piVar1 != packetQueue + 2 && (iVar3 != 0)); iVar3 = iVar3 + -1) {
        iVar2 = packetQueue[2]; // +0x08: packetList
        if (iVar2 == 0) {
          puVar6 = (undefined4 *)0x0;
        }
        else {
          puVar6 = (undefined4 *)(iVar2 + -4);
        }
        packetQueue[10] = packetQueue[10] + -1; // +0x28: timeBudget
        piVar1 = (int *)puVar6[2]; // +0x08: next packet
        iVar2 = puVar6[1]; // +0x04: prev packet
        *piVar1 = iVar2;
        *(int **)(iVar2 + 4) = piVar1;
        (**(code **)*puVar6)(0); // call packet destructor
        piVar1 = (int *)packetQueue[3];
      }
    }
    piVar1 = this + 2; // +0x08: freeList
    if (piVar1 == (int *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = this + 1; // +0x04: freeListTail
    }
    FUN_00788000(piVar5, packetQueue + 2); // merge free lists
    iVar3 = -1;
    piVar5 = piVar1;
    do {
      piVar5 = (int *)*piVar5;
      iVar3 = iVar3 + 1;
    } while (piVar5 != piVar1);
    this[10] = iVar3; // +0x28: freeListCount
  }
  else {
    piVar1 = packetQueue + 2; // +0x08: packetList
    packetQueue[3] = (int)piVar1; // +0x0C: pendingPackets
    *piVar1 = (int)piVar1;
  }
  uVar4 = 0;
  if (packetQueue[0x17] != 0) { // +0x5C: numGhosts
    do {
      iVar3 = *(int *)(packetQueue[0x16] + uVar4 * 8); // +0x58: ghostArray
      if ((iVar3 != 0) && (iVar3 = iVar3 + -0x48, iVar3 != 0)) {
        FUN_007890a0(iVar3); // process ghost update
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)packetQueue[0x17]);
  }
  fVar7 = (float)packetQueue[9]; // +0x24: timeScale
  if ((_DAT_00d577a0 < fVar7) && ((float)this[9] <= fVar7 && fVar7 != (float)this[9])) {
    this[9] = (int)fVar7; // +0x24: timeScale
  }
  FUN_00788720(); // cleanup or finalize
  return;
}