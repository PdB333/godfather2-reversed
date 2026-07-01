//FUNC_NAME: EventProcessor::handleEvent
void __thiscall EventProcessor::handleEvent(int *this, int *eventData)
{
  uint *puVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  bool bCarry;

  iVar4 = *eventData;
  if (iVar4 == kMsgTimerTick) {
    // Increment 64-bit timer at offset +0x20 (this[8] and this[9])
    puVar1 = (uint *)(this + 8);
    bCarry = CARRY4(*puVar1, kTimerIncrement);
    *puVar1 = *puVar1 + kTimerIncrement;
    this[9] = this[9] + (uint)bCarry;
    return;
  }
  if (iVar4 == kMsgUpdate) {
    // Update tick delta
    getSystemTime();
    uVar3 = getCurrentTick();
    iVar4 = uVar3 - this[5]; // delta from last tick
    if (uVar3 < (uint)this[5]) {
      iVar4 = iVar4 + -1; // handle wrap-around
    }
    this[5] = uVar3;
    // Call virtual function at vtable+0x28 (likely onTick)
    (**(code **)(*this + 0x28))(iVar4);
    return;
  }
  if (iVar4 == kMsgStart) {
    debugPrint(&kMsgStart);
    onStart();
    return;
  }
  if (iVar4 == kMsgStateChange) {
    if (this[0xb] == 0) { // offset +0x2c
      onIdle();
      return;
    }
    cVar2 = isReady();
    if (cVar2 != '\0') {
      setState(0x10); // e.g., STATE_ACTIVE
      return;
    }
    setState(1); // e.g., STATE_IDLE
    return;
  }
  if (iVar4 == kMsgStop) {
    debugPrint(&kMsgStop);
    onStop();
    return;
  }
  if (iVar4 == kMsgSetFlag) {
    this[4] = this[4] | 0x80; // set bit 7 at offset +0x10
    return;
  }
  if (iVar4 == kMsgClearFlag) {
    this[4] = this[4] & 0xffffff7f; // clear bit 7
  }
  return;
}