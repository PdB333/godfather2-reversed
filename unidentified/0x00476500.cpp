// FUN_00476500: GhostConnection::resolveGhostSlotIndices

void __thiscall GhostConnection::resolveGhostSlotIndices(int *this, int *pPacketId)
{
  int iCount;
  bool bUnresolvedSlots;
  int iIndex;
  int iFoundIdx;
  int *pGhostEntry;
  int iGlobalCount;
  int *pGlobalTable;
  char cReady;
  int *pSlot;

  // g_pGhostManager is global pointer to the ghost database/manager
  int *pGhostMgr = DAT_01223428;

  // Check if the packet ID matches expected ID at this[6] ( +0x18)
  if (*pPacketId == this[6]) {
    // Pending ghost slots start at this + 0xc (byte offset 0x30)
    pSlot = this + 0xc; // begin of pending slot array (8 slots, each 2 ints)
    bUnresolvedSlots = false;

    // Loop over 8 pending slots ( until this + 0x1c, byte offset 0x70 )
    while (pSlot != this + 0x1c) {
      // If slot ID is non-zero and localIndex is -1 (unresolved)
      if ((*pSlot != 0) && (pSlot[1] == -1)) {
        // Look up ghost ID in global ghost table
        iGlobalCount = *(int *)(pGhostMgr + 0x28); // table size ( +0xa0? )
        iFoundIdx = -1;
        if (0 < iGlobalCount) {
          pGlobalTable = *(int **)(pGhostMgr + 0x24); // pointer to table entries ( +0x90 )
          iIndex = 0;
          do {
            iFoundIdx = iIndex;
            if (*pGlobalTable == *pSlot) break;
            iIndex = iIndex + 1;
            pGlobalTable = pGlobalTable + 5; // each entry is 5 ints (20 bytes)
            iFoundIdx = -1;
          } while (iIndex < iGlobalCount);
        }
        pSlot[1] = iFoundIdx;
        if (pSlot[1] == -1) {
          bUnresolvedSlots = true;
        }
      }
      pSlot = pSlot + 2; // advance to next slot (2 ints = 8 bytes)
    }

    // If any slot remained unresolvable, trigger error handling
    if (bUnresolvedSlots) {
      // FUN_004088c0: probably handleConnectionError, passes this if valid (0x3c sentinel)
      handleGhostError(-(uint)(this != (int *)0x3c) & (uint)this);
      return;
    }

    // Clear pending slots array ( this+6 is offset +0x18 )
    clearPendingSlotsList(this + 6);

    // Check virtual function at vtable[1] (is object ready to process?)
    cReady = (**(code **)(this[5] + 4))(0xffffffff, 0);
    if ((cReady == '\0') && (pSlot = this, this != this + 0x10)) {
      // Loop over resolved ghost slots at start of object (offset 0)
      do {
        if (*pSlot != 0) {
          // Process ghost: access array at this[0x25] ( +0x94 ) with index pSlot[1]
          processGhostUpdate(this[0x25] + pSlot[1] * 0x14);
        }
        pSlot = pSlot + 2;
      } while (pSlot != this + 0x10);
    }
  }
  return;
}