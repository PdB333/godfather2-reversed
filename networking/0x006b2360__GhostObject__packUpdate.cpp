// FUNC_NAME: GhostObject::packUpdate
undefined4 __thiscall GhostObject::packUpdate(int this, uint *buffer) {
  uint flagsMasked;
  bool bVar1;
  float stateTimeFloat;
  uint uVar3;

  // Copy ID from +0x38
  *buffer = *(uint *)(this + 0x38);
  // Copy and mask flags from +0x34, keeping only bits in 0x17DA17FD
  flagsMasked = *(uint *)(this + 0x34) & 0x17da17fd;
  buffer[1] = flagsMasked;
  // Copy two next fields (likely position/rotation)
  buffer[2] = *(uint *)(this + 0x40);
  buffer[3] = *(uint *)(this + 0x3c);

  // Handle action state at +0x16C
  int actionState = *(int *)(this + 0x16C);
  if (actionState == 4) {
    buffer[4] = 3;  // Special mapping: state 4 -> 3
    uVar3 = 3;
  } else {
    buffer[4] = actionState;
    buffer[5] = *(uint *)(this + 0x170); // state time or duration
    if (actionState != 0 || ((*(uint *)(this + 0x34) >> 0x1c) & 1) != 0) {
      goto DONE_STATE;
    }
    // Additional flag processing for state 0 with specific bits
    bVar1 = ((*(uint *)(this + 0x34) >> 0x12) & 1) == 0; // check bit 18
    if (!bVar1) {
      buffer[1] |= 0x80000; // set bit 19 in flags
    }
    if ((*(byte *)(this + 0x36) & 1) == 0) {
      if (bVar1) goto DONE_STATE;
    } else {
      buffer[1] |= 0x20000; // set bit 17
    }
    buffer[4] = 1; // override state to 1
    uVar3 = 1;
  }
  // Convert state to float (likely time or normalized value)
  stateTimeFloat = stateTimeToFloat(uVar3);  // FUN_006b20f0
  buffer[5] = *(uint *)&stateTimeFloat;

DONE_STATE:
  // Remaining fields (position, velocity, etc.)
  buffer[6] = 0; // zero placeholder
  buffer[7] = *(uint *)(this + 0x5C);
  buffer[8] = *(uint *)(this + 0x60);
  buffer[9] = *(uint *)(this + 0x68);
  buffer[10] = *(uint *)(this + 0x6C);
  buffer[11] = *(uint *)(this + 0x74);
  buffer[12] = *(uint *)(this + 0x7C);
  buffer[13] = *(uint *)(this + 0x80);
  buffer[14] = *(uint *)(this + 0x88);
  buffer[15] = *(uint *)(this + 0xA0);
  buffer[16] = *(uint *)(this + 0x64); // offset 100 decimal
  buffer[17] = *(uint *)(this + 200);  // offset 0xC8
  buffer[18] = 0; // zero
  buffer[19] = *(uint *)(this + 0x174);
  buffer[20] = *(uint *)(this + 0x178);
  buffer[21] = 0;
  buffer[22] = 0;
  buffer[23] = 0;
  return 0x60; // total bytes written (24 dwords)
}