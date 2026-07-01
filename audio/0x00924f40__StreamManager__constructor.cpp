// FUNC_NAME: StreamManager::constructor
undefined4 * __fastcall StreamManager::constructor(undefined4 *this)

{
  undefined8 *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  int local_4;
  
  // Call base class constructor
  EARSObject::constructor();
  
  // Set vtable pointers and initial state
  this[0x13] = &UNK_DATA_00d87320;   // +0x4C - vtable or interface pointer
  DAT_01129c48 = this;                // Global instance pointer
  *this = &VTABLE_00d87350;           // +0x00 - vtable
  this[4] = &UNK_DATA_00d87328;      // +0x10 - another interface
  this[0x13] = &UNK_DATA_00d87324;   // +0x4C
  this[0x14] = 0;                     // +0x50 - stream count
  this[0x15] = 0xffffffff;           // +0x54 - some ID, -1 = invalid
  this[0x16] = 5;                     // +0x58 - max simultaneous streams (5)
  this[0x17] = 0xffffffff;           // +0x5C - another ID
  this[0x18] = 0;                     // +0x60
  this[0x19] = 0;                     // +0x64
  this[0x1a] = 0;                     // +0x68
  this[0x1b] = 0;                     // +0x6C
  this[0x1c] = 0;                     // +0x70
  this[0x1d] = 0;                     // +0x74
  this[0x1e] = 0;                     // +0x78
  *(undefined1 *)(this + 0x1f) = 0;   // +0x7C - byte
  this[0x20] = 0;                     // +0x80
  
  // Initialize stream data pools (5 types * 2 streams each = 10 stream slots)
  puVar3 = &DAT_00e564f4;            // Pointer to stream configuration data
  local_4 = 5;                        // 5 stream types
  do {
    uVar4 = 0;
    if (*puVar3 != 0) {
      iVar5 = 0;
      do {
        puVar1 = (undefined8 *)(puVar3[1] + iVar5 + 8);  // +0x8 offset for stream data
        iVar2 = 2;                    // 2 streams per type (ping-pong)
        do {
          *puVar1 = 0;                // Clear stream data
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = 0;
          *(undefined8 **)(puVar1 + 4) = puVar1;  // Self-link for circular buffer
          *(undefined4 *)((int)puVar1 + 0x24) = 0;   // +0x24 - some offset
          *(undefined4 *)(puVar1 + 5) = 0xffffffff;  // +0x28 - ID, -1 = invalid
          puVar1 = puVar1 + 6;        // Each stream entry is 6*8 = 48 bytes
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        uVar4 = uVar4 + 1;
        iVar5 = iVar5 + 100;          // 100 bytes per stream slot
      } while (uVar4 < *puVar3);
    }
    puVar3 = puVar3 + 2;              // Next stream type configuration
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  
  return this;
}