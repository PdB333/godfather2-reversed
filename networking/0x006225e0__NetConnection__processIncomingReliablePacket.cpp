// FUNC_NAME: NetConnection::processIncomingReliablePacket

undefined4 * NetConnection::processIncomingReliablePacket(int this, undefined4 *outBuffer, uint *sequenceNum, int owner, int packetData)
{
  char cVar1;
  undefined4 *puVar2;
  bool bVar3;
  int local_c;
  int local_8;
  
  // Check if connection is active (offset +0x20 likely connection state or initialized flag)
  if (*(int *)(this + 0x20) == 0) {
    FUN_00623310(this, outBuffer, 1, sequenceNum);
    return outBuffer;
  }
  
  // Get the send window pointer from +0x1c (pointer to pointer to packet window)
  local_8 = **(int **)(this + 0x1c);
  
  // Validate caller context: must be non-null and equal to this
  if ((owner == 0) || (owner != this)) {
    FUN_00b97aea(); // likely lock or assertion
  }
  
  // Compare packetData with current send window (local_8)
  if (packetData == local_8) {
    // Packet belongs to current send window
    if (*sequenceNum < *(uint *)(packetData + 0xc)) {
      FUN_00623310(this, outBuffer, 1, sequenceNum);
      return outBuffer;
    }
  }
  else {
    // Packet belongs to different window
    local_8 = *(int *)(this + 0x1c); // re-fetch window pointer
    if ((owner == 0) || (owner != this)) {
      FUN_00b97aea();
    }
    if (packetData == local_8) {
      // Now packet matches after re-fetch
      if (*(uint *)(*(int *)(*(int *)(this + 0x1c) + 8) + 0xc) < *sequenceNum) {
        FUN_00623310(this, outBuffer, 0, sequenceNum);
        return outBuffer;
      }
    }
    else {
      // Still different window
      bVar3 = *(uint *)(packetData + 0xc) < *sequenceNum;
      if (*sequenceNum < *(uint *)(packetData + 0xc)) {
        FUN_00624370(); // some update function
        if (*(uint *)(packetData + 0xc) < *sequenceNum) {
          // Check flag at +0x15 of packet's header (reliable flag?)
          if (*(char *)(*(int *)(packetData + 8) + 0x15) == '\0') {
            FUN_00623310(this, outBuffer, 1, sequenceNum);
            return outBuffer;
          }
          FUN_00623310(this, outBuffer, 0, sequenceNum);
          return outBuffer;
        }
        bVar3 = *(uint *)(packetData + 0xc) < *sequenceNum;
      }
      if (bVar3) {
        local_8 = *(int *)(this + 0x1c);
        local_c = this;
        FUN_006243f0(); // advance window or something
        cVar1 = FUN_00622a60(); // check duplicate flag
        if ((cVar1 != '\0') || (*sequenceNum < *(uint *)(packetData + 0xc))) {
          if (*(char *)(*(int *)(packetData + 8) + 0x15) == '\0') {
            FUN_00623310(this, outBuffer, 1, sequenceNum);
            return outBuffer;
          }
          FUN_00623310(this, outBuffer, 0, sequenceNum);
          return outBuffer;
        }
      }
    }
  }
  
  // Copy packet data from the send window
  puVar2 = (undefined4 *)FUN_00623130(this, &local_c, sequenceNum);
  *outBuffer = *puVar2;
  outBuffer[1] = puVar2[1];
  return outBuffer;
}