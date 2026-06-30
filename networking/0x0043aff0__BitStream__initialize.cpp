// FUNC_NAME: BitStream::initialize
// Function at 0x0043aff0 - Parses a packet buffer header and initializes the bitstream for reading.
// TNL packet format: flags at +0x1c, count at +0x1f, index at +0x1e,
// then table of (id, bitCount) entries followed by bit data.
// param_2: pointer to packet buffer
// param_3: packet sequence number (stored at +0x60)

void __thiscall BitStream::initialize(char* packetBuffer, int sequenceNumber)
{
  int iVar1;
  byte entryCount;
  int* entryPtr;
  uint index;
  byte currentEntry;
  
  // +0x60: packet sequence number
  *(int*)(this + 0x60) = sequenceNumber;
  
  // Check flags at packetBuffer+0x1c bit 0
  // If clear: simple packet (no per-message bit count table)
  if ((*(byte*)(packetBuffer + 0x1c) & 1) == 0) {
    // +0x5c: pointer to data after header (offset 0x20 from packet buffer)
    *(char**)(this + 0x5c) = packetBuffer + 0x20;
    // +0x00: flag = 0 (simple mode)
    *(int*)this = 0;
    // +0x0c: message type = -1 (unused in simple mode)
    *(int*)(this + 0x0c) = 0xffffffff;
    // +0x10: data size = 0 (no per-message data)
    *(int*)(this + 0x10) = 0;
    // Call helper to set up bit buffer pointers or similar
    FUN_0043b140();
  }
  else {
    // Complex packet: has per-message bit count table
    *(int*)this = 1;
    entryCount = *(byte*)(packetBuffer + 0x1f);
    if (entryCount != 0) {
      // Calculate start of entry table: packetBuffer + 0x2c + (offsetIndex*4)
      // where offsetIndex is at packetBuffer+0x1e
      iVar1 = packetBuffer + 0x2c + (uint)*(byte*)(packetBuffer + 0x1e) * 4;
      index = 0;
      do {
        // Each entry: *(int*)entryBase + entryOffset ?? This looks like an indirect index.
        // Actually it reads a pointer from table, then adds index*4 again? Possibly a relocation.
        entryPtr = (int*)(*(int*)(index * 4 + iVar1) + index * 4 + iVar1);
        if (*entryPtr == sequenceNumber) {
          // Found matching entry
          // +0x0c: message type = 0 (maybe indicates found)
          *(int*)(this + 0x0c) = 0;
          // +0x10: bit count from entry (ushort at entryPtr+1)
          index = (uint)*(ushort*)(entryPtr + 1);
          *(uint*)(this + 0x10) = index;
          if (index != 0) {
            // +0x04: pointer to start of bit data (right after entry ptr)
            *(char**)(this + 4) = (char*)entryPtr + 6;
            // +0x08: byte-aligned pointer (rounded up to 4 bytes)
            *(uint*)(this + 8) = ((uint)((int)(entryPtr + 6) + (index + 7) / 8 + 3) & 0xfffffffc);
          }
          goto LAB_0043b058;
        }
        currentEntry = (byte)(index + 1);
        index = (uint)currentEntry;
      } while (currentEntry < entryCount);
    }
    // No matching entry found
    *(int*)(this + 0x0c) = 0;
    *(int*)(this + 0x10) = 0;
    
LAB_0043b058:
    if (*(int*)(this + 0x10) != 0) {
      // Set magic header for the bit data: 0x25e3 (maybe packet type or compression flag)
      *(short*)(this + 0x1a) = 0x25e3;
      // +0x18: low word of message type (from +0x0c)
      *(short*)(this + 0x18) = *(short*)(this + 0x0c);
      // Check first byte of bit data: if bit 0 set, data is empty
      if ((**(byte**)(this + 4) & 1) != 0) {
        *(int*)(this + 0x14) = 0;
        *(int*)(this + 0x1c) = 0;
        return;
      }
      // Otherwise, read first dword from byte pointer and advance
      *(int**)(this + 0x14) = *(int**)(this + 8);
      *(int*)(this + 0x1c) = **(int**)(this + 8);
      *(int*)(this + 8) = *(int*)(this + 8) + 4;
    }
  }
  return;
}