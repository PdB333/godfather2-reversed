// FUNC_NAME: NetPacket::NetPacket

NetPacket * __thiscall NetPacket::NetPacket(NetPacket *this, undefined4 param_2)
{
  uint timeStamp;
  uint timeStamp2;
  
  // Base class constructor call (likely BaseNetPacket or SimObject)
  BaseNetPacket::BaseNetPacket(param_2);
  
  // Set vtable pointers (multiple inheritance)
  *this = &NetPacket_vtable;                // +0x00: vtable for NetPacket
  this[0xf] = &NetPacket_vtable2;           // +0x3c: second vtable
  this[0x12] = &NetPacket_vtable3;          // +0x48: third vtable
  
  // Clear or initialize packet fields
  this[0x14] = 0;                           // +0x50: field1
  *(short *)(param_1 + 0x15) = 0;           // +0x54: short field (offset 0x54)
  *(short *)((int)param_1 + 0x56) = 0;      // +0x56: short field
  this[0x16] = 0;                           // +0x58: field2
  *(short *)(param_1 + 0x17) = 0;           // +0x5c: short field (offset 0x5c)
  *(short *)((int)param_1 + 0x5e) = 0;      // +0x5e: short field
  this[0x18] = 0;                           // +0x60: field3
  *(short *)(param_1 + 0x19) = 0;           // +0x64: short field (offset 0x64)
  *(short *)((int)param_1 + 0x66) = 0;      // +0x66: short field
  this[0x1a] = 0;                           // +0x68: field4
  *(short *)(param_1 + 0x1b) = 0;           // +0x6c: short field (offset 0x6c)
  *(short *)((int)param_1 + 0x6e) = 0;      // +0x6e: short field
  this[0x1c] = 0;                           // +0x70: field5
  
  // Initialize debug sentinel values (for buffer corruption detection)
  this[0x1d] = 0xbadbadba;                  // +0x74: magic1
  this[0x1e] = 0xbeefbeef;                  // +0x78: magic2
  this[0x1f] = 0xeac15a55;                  // +0x7c: magic3
  this[0x20] = 0x91100911;                  // +0x80: magic4
  
  timeStamp = getTimeStamp();               // Get current time or random seed
  this[0x21] = timeStamp;                   // +0x84: timestamp field
  this[0x22] = 0;                           // +0x88: clear
  
  // Clear the sentinel area (marks as unused/freed)
  this[0x20] = 0;
  this[0x1f] = 0;
  this[0x1e] = 0;
  this[0x1d] = 0;
  
  // Another set of sentinel values for a different region
  this[0x23] = 0xbadbadba;                  // +0x8c: magic5
  this[0x24] = 0xbeefbeef;                  // +0x90: magic6
  this[0x25] = 0xeac15a55;                  // +0x94: magic7
  this[0x26] = 0x91100911;                  // +0x98: magic8
  
  timeStamp2 = getTimeStamp();              // Second timestamp
  this[0x27] = timeStamp2;                  // +0x9c: another timestamp
  this[0x28] = 0;                           // +0xa0: clear
  
  // Clear second sentinel region
  this[0x26] = 0;
  this[0x25] = 0;
  this[0x24] = 0;
  this[0x23] = 0;
  
  // Initialize global static data
  this[0x29] = DAT_00d5d934;                // +0xa4: global data 1
  this[0x2a] = DAT_00d5d740;                // +0xa8: global data 2
  
  // Copy data from a global array/struct
  uint globalData = _DAT_00d5780c;          // Reference to static data
  this[0x2b] = globalData;                  // +0xac: copy 1
  this[0x2c] = globalData;                  // +0xb0: copy 2
  this[0x2d] = globalData;                  // +0xb4: copy 3
  this[0x2e] = globalData;                  // +0xb8: copy 4
  this[0x2f] = 0;                           // +0xbc: zero
  this[0x30] = 0;                           // +0xc0: zero
  this[0x31] = 0;                           // +0xc4: zero
  this[0x32] = globalData;                  // +0xc8: copy 5
  this[0x33] = globalData;                  // +0xcc: copy 6
  this[0x34] = 0;                           // +0xd0: zero
  this[0x35] = globalData;                  // +0xd4: copy 7
  this[0x36] = globalData;                  // +0xd8: copy 8
  this[0x37] = 0;                           // +0xdc: zero
  this[0x38] = globalData;                  // +0xe0: copy 9
  this[0x39] = globalData;                  // +0xe4: copy 10
  *(byte *)(param_1 + 0x3a) = 0;            // +0xe8: byte field
  *(byte *)((int)param_1 + 0xe9) = 0;       // +0xe9: byte field
  
  return this;
}