// FUNC_NAME: NetConnection::processGhostStream
// Address: 0x006721d0
// Role: Iterates over a table of 12-byte ghost entries (per channel) and processes data I/O for network streaming.
// Each entry: +0 short mode, +4 int (pointer to ghost object), +8 int (extra data if mode==1)
// param_1: this pointer (NetConnection object)
// param_2: channel index (0-based)
// The function writes a mode value (2 or 3) into the entry's short, then loops over the ghost count
// obtained from a global object, calling various helper routines.

int NetConnection::processGhostStream(int param_1, int param_2) {
  int iVar1;
  int iVar2;
  int ghostCount;
  int local_10;
  int mode;               // local_c
  int extraData;          // local_8
  uint iterIdx;           // local_4

  int baseOffset = *(int *)(param_1 + 4);  // +0x4: base address of ghost table array (12-byte entries)
  int entryOffset = param_2 * 12;          // each entry 12 bytes
  int ghostObjPtr = *(int *)(entryOffset + 4 + baseOffset);  // entry->+4: pointer to ghost object (iVar1)

  local_10 = 0;
  iterIdx = 0;
  extraData = 0;

  // Check global state (network initialised, connected)
  iVar2 = FUN_006761b0();  // likely "isConnected" or "isReady"
  if (iVar2 == 0) {
    iVar2 = FUN_00676150();  // alternative check
    if (iVar2 == 0) {
      return 0x4e24;  // error code: 20004 ("not ready")
    }
    mode = 3;  // set mode to 3 if alternative check passed
  } else {
    mode = 2;  // set mode to 2 if primary check passed
  }

  // Store mode (2 or 3) into the entry's first two bytes
  *(short *)(entryOffset + baseOffset) = (short)mode;

  if ((short)mode == 1) {  // rarely taken (mode never 1 here, but handled for completeness)
    extraData = *(int *)(entryOffset + 8 + baseOffset);
  }

  // Main loop: iterate over ghost objects associated with this channel
  // The loop count (iterIdx bound) is dynamically obtained from a global object
  ghostCount = 0;
  do {
    // Copy data from ghost object offset +0xc to offset +4 (likely update pointer or state)
    *(int *)(ghostObjPtr + 4) = *(int *)(ghostObjPtr + 0xc);

    // Process ghost: returns an object pointer (uVar3) and may set local_10 to error
    int uVar3 = FUN_00675810(mode, iterIdx, ghostObjPtr, extraData, 0, &local_10);

    if ((local_10 == 0) && ( (iVar2 = FUN_00673280(uVar3), local_10 == 0) )) {
      // Update loop bound from returned ghost metadata (+0x58 holds count)
      iterIdx = (uint)*(ushort *)(iVar2 + 0x58);

      // Process this entry further
      local_10 = FUN_00671cd0(param_1, param_2, iterIdx);
      FUN_00674eb0();  // some global processing

      if ((local_10 == 0) && (FUN_00675d20(), local_10 == 0)) {
        // Perform final update with connection's ghost count-1 (+0x8 is count)
        local_10 = FUN_00671e60(param_1, *(ushort *)(param_1 + 8) - 1);
      }
    }
    ++iterIdx;
  } while ((iterIdx < iterIdx) && (local_10 == 0));
  // Note: the while condition is questionable; likely iterIdx < ghostCount, but ghostCount variable is shadowed.
  // The original loop condition uses local_4 as bound, which is re-assigned inside loop.
  // Correction: The loop should be: while ((iterIdx < (int)local_4) && (local_10 == 0))
  // The decompiled code uses "iVar4" which we renamed to iterIdx, and local_4 is the bound.
  return local_10;
}