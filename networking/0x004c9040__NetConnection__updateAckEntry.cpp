// FUNC_NAME: NetConnection::updateAckEntry

void __fastcall NetConnection::updateAckEntry(int this, int typeFlags, int *ackTable)
{
  int slotIdx = 0;
  int *slotPtr = ackTable;

  // Search for slot matching this (connection?) and typeFlags
  while (slotPtr[4] != this || slotPtr[5] != typeFlags)
  {
    slotIdx++;
    slotPtr += 5; // stride of 5 ints between slot keys
    if (slotIdx > 0x1f)
      return;
  }
  if (slotIdx != -1)
  {
    // Initialize slot data at offsets +6, +7, +8 relative to slot start
    ackTable[slotIdx * 5 + 6] = DAT_01205224; // global tick / timestamp
    ackTable[slotIdx * 5 + 7] = 0;            // reserved / status
    ackTable[slotIdx * 5 + 8] = -1;           // invalid ID

    if (typeFlags == 1)
    {
      int *pTimestamp = (int *)FUN_005e68f0(); // get 64-bit system time
      if (pTimestamp != (int *)0x0)
      {
        ackTable[slotIdx * 5 + 7] = *pTimestamp;
        ackTable[slotIdx * 5 + 8] = pTimestamp[1];
      }
    }
    else if (typeFlags == 2)
    {
      FUN_005e30c0(); // some initialization
      char localBuffer[96];
      bool success = FUN_005e2180(localBuffer); // get peer address?
      if (success)
      {
        ackTable[slotIdx * 5 + 7] = iStack_c;
        ackTable[slotIdx * 5 + 8] = iStack_8;
      }
    }
  }
}