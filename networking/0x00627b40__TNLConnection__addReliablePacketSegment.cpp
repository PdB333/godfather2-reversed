// FUNC_NAME: TNLConnection::addReliablePacketSegment
void TNLConnection::addReliablePacketSegment(void) {
  // this pointer in EAX
  int* pBufferBase;
  int iResult;
  int nLogLine;
  char szBuf[68]; // Debug buffer

  // Check if debug logging is enabled
  iResult = FUN_00632b70(); // Some debug flag check
  if (iResult != 0) {
    FUN_00632fb0(); // Get debug location info (file/line)
    if (0 < nLogLine) {
      FUN_00625d40("%s:%d: ", szBuf, nLogLine); // Print debug message
      return; // Early exit if debug logging
    }
  }

  // Check send window: if send sequence <= last acked sequence, flush
  // Offsets: this+0x10 -> connection state pointer
  // +0x20 = mSendSeq, +0x24 = mAckSeq (or similar)
  int* pConnState = *(int**)(this + 0x10);
  if (*(unsigned int*)(pConnState + 0x20) <= *(unsigned int*)(pConnState + 0x24)) {
    FUN_00627360(); // Flush or send pending packets
  }

  // Write packet segment header: type=4 (e.g., ReliableOrdered) followed by a DWORD (seq or timestamp)
  pBufferBase = *(int**)(this + 0x8); // Current write pointer in send buffer
  *pBufferBase = 4; // Segment type
  unsigned int uVal = FUN_00638920(); // Get sequence number or time
  *(pBufferBase + 1) = uVal;
  // Advance write pointer by 8 bytes (type + data)
  *(int*)(this + 0x8) = (int)(pBufferBase + 2);
}