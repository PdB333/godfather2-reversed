// FUNC_NAME: NetSession::processIncomingPacket
void __thiscall NetSession::processIncomingPacket(int *this, int *packetData)
{
  code *vtableFunc;
  char isActive;
  undefined4 result;
  int *hashPtr;
  int stackHash[4];
  int stackHashCopy[4];
  undefined1 buffer[48];
  undefined1 tempBuffer[28];
  
  isActive = (**(code **)(*this + 0x2c))(); // Check if session is active
  if (isActive == '\0') {
    if (this[0x34] != 0) { // +0xD0: some flag
      FUN_004df600(); // Log error
    }
    vtableFunc = *(code **)(*this + 0x3c); // +0x3C: vtable function for cleanup
    this[0x35] = 0; // +0xD4: packet hash
    (*vtableFunc)(0);
    return;
  }
  
  if (this[0x34] != 0) { // +0xD0: flag check
    // Calculate hash of packet data
    if (this[0x35] != ((*packetData * 0x21 + packetData[1]) * 0x21 + packetData[2]) * 0x21 + packetData[3]) {
      FUN_004df600(); // Hash mismatch - log error
    }
    if (this[0x34] != 0) goto LAB_006cfd7a; // +0xD0: flag check
  }
  
  this[0x35] = 0; // +0xD4: reset packet hash
  
  // Check for known magic values or zero hash
  if (((((*packetData != -0x45245246) || (packetData[1] != -0x41104111)) || (packetData[2] != -0x153ea5ab))
      || (packetData[3] != -0x6eeff6ef)) &&
     (((*packetData != 0 || (packetData[1] != 0)) || ((packetData[2] != 0 || (packetData[3] != 0)))))) {
    // Not a known magic or zero hash - process packet
    FUN_00412d90(buffer); // Initialize buffer
    (**(code **)(*this + 0x24))(tempBuffer); // +0x24: get session key
    
    stackHashCopy[0] = packetData[0];
    stackHashCopy[1] = packetData[1];
    stackHashCopy[2] = packetData[2];
    stackHashCopy[3] = packetData[3];
    
    result = 0;
    // Decrypt/verify packet data
    uVar3 = FUN_004df270(&stackHash[0], &stackHashCopy[0], buffer, 0x1ff, 0, &result);
    FUN_00414db0(uVar3); // Process decrypted data
    
    if (stackHash[0] != 0) {
      *(undefined4 *)(stackHash[0] + 8) = 0; // Clear some field
    }
    
    hashPtr = (int *)FUN_00445210(&stackHash[0]); // Get hash from processed data
    this[0x35] = *hashPtr; // +0xD4: store packet hash
    FUN_004df710(); // Cleanup
    *(undefined1 *)(this + 0x62) = 0; // +0x188: reset some flag
  }
  
LAB_006cfd7a:
  (**(code **)(*this + 0x3c))(1); // +0x3C: signal packet processed
  return;
}