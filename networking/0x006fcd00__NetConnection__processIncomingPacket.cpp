// FUNC_NAME: NetConnection::processIncomingPacket

// 0x006fcd00 - Process an incoming reliable data packet.
// Locks a global packet mutex, validates the packet, copies data, parses header,
// and extracts packet sequence/type from the buffer structure.
// Returns 1 on success, 0 on failure or if state invalid.

bool __thiscall NetConnection::processIncomingPacket(void *data, size_t dataSize)
{
  int state;
  void *buffer;
  int bufferSize;
  bool isValid;
  int *headerPtr;
  int seqNum;

  // Check for valid data and that we are in a receptive state (1 or 6)
  if (data == nullptr || (this->mState != 1 && this->mState != 6))
    return false;

  // Lock global packet processing mutex
  mutexLock(&gPacketMutex);

  // If we have a buffer allocated
  if (this->mPacketBuffer != nullptr)
  {
    // If state is 6, flush any pending data before processing
    if (this->mState == 6)
    {
      flushSendBuffer(); // 0x006fbd30
    }

    // Ensure we have a buffer and the incoming data fits
    if (this->mPacketBuffer != nullptr && dataSize <= (size_t)this->mBufferSize)
    {
      // Copy packet data into the internal buffer
      memcpy(this->mPacketBuffer, data, dataSize);

      // Validate and parse the packet header (e.g., sequence number, type)
      buffer = this->mPacketBuffer;
      isValid = validatePacketHeader(buffer); // 0x006fcc30

      if (isValid)
      {
        // Successful packet – update state to "processed" (2)
        this->mState = 2;
        this->mSomething = 0;

        // Extract the first sequence/ID from the packet's header structure.
        // The packet buffer (at offset 0) is a structure where:
        //   +0x2c : count or length (int)
        //   +0x30 : pointer to an array of pointers (e.g., to packet segments)
        if (*(int *)((char *)buffer + 0x2c) > 0 &&
            * (int **)((char *)buffer + 0x30) != nullptr)
        {
          // Read the first uint from the first pointer's data
          this->mPacketID = *(int *)* (int **)((char *)buffer + 0x30);
          mutexUnlock(&gPacketMutex);
          return true;
        }

        // If no valid data in header, reset state to error/retry (6)
        this->mSomething = 0;
        this->mState = 6;
      }
    }
  }

  // Unlock and indicate failure
  mutexUnlock(&gPacketMutex);
  return false;
}