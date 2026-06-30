// FUNC_NAME: NetConnection::buildPacketHeader
void __thiscall NetConnection::buildPacketHeader(int thisPtr, undefined4 *packetHeader)
{
  int connectionState;
  int packetWindow;
  char statusFlag;
  int tempVar;
  undefined4 value;
  uint stackVar1;
  undefined4 stackVar2;
  
  // Check magic number at the start of packetHeader - likely a packet type identifier
  int magic = (**(code (***)(void))*packetHeader)();
  if (magic != 0x6862a74c) {
    // Invalid magic, call error handler
    FUN_0073e4d0(packetHeader);
    return;
  }
  
  // Get connection state object (offset 0x5c from this)
  connectionState = *(int *)(thisPtr + 0x5c);
  // Get packet window slot (offset 0x21e4 from connection state)
  packetWindow = *(int *)(connectionState + 0x21e4);
  
  if (packetWindow != 0) {
    // Validate window slot state
    statusFlag = FUN_00767480(packetWindow);
    FUN_0072cb10(statusFlag);
    // Update ack/sequence data
    FUN_0075cd50(packetWindow + 0x44);
    FUN_0075cd70(_DAT_00d5cf70);
    
    // Write 64-bit sequence number (low part from function, high part from connectionState)
    *(ulonglong *)(packetHeader + 0x1e) = CONCAT44(FUN_007347e0, connectionState);
    // Write another 64-bit field (seems to be a function pointer + stack value)
    *(ulonglong *)(packetHeader + 0x20) = (ulonglong)stackVar1 << 0x20;
    *(ulonglong *)(packetHeader + 0x22) = CONCAT44(&LAB_0073b090, stackVar2);
    // Write ack mask
    *(ulonglong *)(packetHeader + 0x24) = CONCAT44(FUN_0072f880, connectionState);
    *(ulonglong *)(packetHeader + 0x26) = (ulonglong)stackVar1 << 0x20;
    *(ulonglong *)(packetHeader + 0x28) = CONCAT44(&LAB_0074a150, stackVar2);
    
    // Get packet window buffer from another offset (0x24c4)
    int windowBuffer = *(int *)(*(int *)(thisPtr + 0x5c) + 0x24c4);
    if (windowBuffer == 0) {
      windowBuffer = 0;
    } else {
      windowBuffer = windowBuffer + -0x48;
    }
    FUN_0074a210(windowBuffer);
    
    // Get current timestamp
    value = FUN_00800b60();
    packetHeader[0x2b] = value;
    
    // Call virtual function at offset 0x270 from connection state object
    (**(code **)(**(int **)(thisPtr + 0x5c) + 0x270))();
    packetHeader[0x41] = thisPtr + 0x70; // Store pointer to internal data
    
    // Check if connection is active and additional condition
    bool isConnected;
    if ((statusFlag == '\0') && (isConnected = FUN_0072d880(), isConnected != '\0')) {
      isConnected = true;
    } else {
      isConnected = false;
    }
    
    if (isConnected) {
      // Set flag bit 0 in packet header flags
      packetHeader[0x2a] = packetHeader[0x2a] | 1;
    } else {
      // Clear flag bit 0
      packetHeader[0x2a] = packetHeader[0x2a] & 0xfffffffe;
    }
  }
  return;
}