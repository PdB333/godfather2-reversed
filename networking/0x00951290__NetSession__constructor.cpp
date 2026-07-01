// FUNC_NAME: NetSession::constructor
undefined4 * __fastcall NetSession::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  // Call base class constructor
  FUN_00957ed0();
  
  // Set vtable pointers
  this[0x14] = &PTR_LAB_00d8bcbc;  // +0x50: vtable for some interface
  DAT_01130038 = this;              // Store singleton pointer
  this[0x15] = &PTR_LAB_00d84f98;  // +0x54: vtable for another interface
  *this = &PTR_FUN_00d8bd00;       // +0x00: main vtable
  this[4] = &PTR_LAB_00d8bcdc;     // +0x10: vtable
  this[0x14] = &PTR_LAB_00d8bcd8;  // +0x50: vtable
  this[0x15] = &PTR_LAB_00d8bcc0;  // +0x54: vtable
  
  // Initialize member variables to 0
  this[0x16] = 0;  // +0x58
  this[0x17] = 0;  // +0x5C
  this[0x18] = 0;  // +0x60
  this[0x19] = 0;  // +0x64
  this[0x1a] = 0;  // +0x68
  this[0x1b] = 0;  // +0x6C
  
  // Initialize connection-related fields
  this[0x1e] = 0xffffffff;  // +0x78: -1 (invalid connection)
  this[0x1f] = 0;           // +0x7C
  this[0x20] = 0xffffffff;  // +0x80: -1 (invalid)
  this[0x26] = 0;           // +0x98
  this[0x27] = 0;           // +0x9C
  this[0x28] = 0xffffffff;  // +0xA0: -1 (invalid)
  *(undefined1 *)(this + 0x29) = 0;  // +0xA4: byte field
  
  // Allocate buffers for packet handling
  uVar1 = FUN_009c8e80(0x20);  // Allocate 32 bytes
  this[0x1c] = uVar1;          // +0x70: buffer pointer
  uVar1 = FUN_009c8e80(0x20);  // Allocate 32 bytes
  this[0x1d] = uVar1;          // +0x74: buffer pointer
  uVar1 = FUN_009c8e80(0x80);  // Allocate 128 bytes
  this[0x21] = uVar1;          // +0x84: buffer pointer
  uVar1 = FUN_009c8e80(0x20);  // Allocate 32 bytes
  this[0x22] = uVar1;          // +0x88: buffer pointer
  uVar1 = FUN_009c8e80(0x20);  // Allocate 32 bytes
  this[0x23] = uVar1;          // +0x8C: buffer pointer
  uVar1 = FUN_009c8e80(0x20);  // Allocate 32 bytes
  this[0x24] = uVar1;          // +0x90: buffer pointer
  puVar2 = (undefined1 *)FUN_009c8e80(0x80);  // Allocate 128 bytes
  this[0x25] = puVar2;         // +0x94: buffer pointer
  
  // Initialize all allocated buffers to 0
  *puVar2 = 0;                 // Clear 128-byte buffer
  *(undefined1 *)this[0x24] = 0;  // Clear 32-byte buffer
  *(undefined1 *)this[0x23] = 0;  // Clear 32-byte buffer
  *(undefined1 *)this[0x22] = 0;  // Clear 32-byte buffer
  *(undefined1 *)this[0x21] = 0;  // Clear 128-byte buffer
  *(undefined1 *)this[0x1d] = 0;  // Clear 32-byte buffer
  *(undefined1 *)this[0x1c] = 0;  // Clear 32-byte buffer
  
  return this;
}