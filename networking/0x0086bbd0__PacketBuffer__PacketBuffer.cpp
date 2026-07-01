// FUNC_NAME: PacketBuffer::PacketBuffer
undefined4 * __thiscall PacketBuffer::PacketBuffer(undefined4 *this, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  // Call base class constructor (likely NetObject or similar)
  BaseClass::BaseClass(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d75eb0; // vtable for PacketBuffer
  
  // Initialize function pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d75e9c; // +0x3C: some callback
  this[0x12] = &PTR_LAB_00d75e98; // +0x48: another callback
  
  // Initialize packet header magic numbers (TNL-style)
  this[0x14] = 0;                // +0x50: reserved
  this[0x15] = 0;                // +0x54: reserved
  this[0x16] = 0xbadbadba;       // +0x58: magic1
  this[0x17] = 0xbeefbeef;       // +0x5C: magic2
  this[0x18] = 0xeac15a55;       // +0x60: magic3
  this[0x19] = 0x91100911;       // +0x64: magic4
  
  puVar1 = this + 0xf;           // pointer to offset +0x3C (used for copy)
  
  // Zero out the rest of the header and payload area
  this[0x1a] = 0;                // +0x68
  this[0x1b] = 0;                // +0x6C
  this[0x1c] = 0;                // +0x70
  this[0x1d] = 0;                // +0x74
  this[0x1e] = 0;                // +0x78
  this[0x20] = 0;                // +0x80
  this[0x21] = 0;                // +0x84
  this[0x22] = 0;                // +0x88
  this[0x23] = 0;                // +0x8C
  this[0x24] = 0;                // +0x90
  this[0x25] = 0;                // +0x94
  this[0x26] = 0;                // +0x98
  this[0x27] = 0;                // +0x9C
  this[0x28] = 0;                // +0xA0
  this[0x29] = 0;                // +0xA4
  this[0x2a] = 0;                // +0xA8
  this[0x2b] = 0;                // +0xAC
  this[0x2c] = 0;                // +0xB0
  
  uVar2 = DAT_00d5f00c;          // some global value (e.g., session key)
  this[0x1f] = 0;                // +0x7C
  this[0x2d] = uVar2;            // +0xB4: store global value
  this[0x2e] = 0;                // +0xB8
  this[0x2f] = 0;                // +0xBC
  this[0x30] = 0;                // +0xC0
  this[0x31] = 0;                // +0xC4
  *(undefined2 *)(this + 0x32) = 0; // +0xC8: short field
  
  // Copy global data into the buffer (likely encryption keys or session data)
  if (DAT_0120e93c != 0) {
    FUN_00408900(puVar1, &DAT_0120e93c, 0x8000); // copy 0x8000 bytes from global to buffer
  }
  if (DAT_0112e12c != 0) {
    FUN_00408900(puVar1, &DAT_0112e12c, 0x8000);
  }
  if (DAT_0112e13c != 0) {
    FUN_00408900(puVar1, &DAT_0112e13c, 0x8000);
  }
  
  // Register this packet buffer with the packet manager (type 0x11)
  FUN_008f6f50(0x11, this);
  
  return this;
}