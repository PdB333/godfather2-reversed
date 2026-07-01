// FUNC_NAME: NetObject::NetObject
undefined4 * __thiscall NetObject::NetObject(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor (likely NetObjectBase or similar)
  FUN_0046c590(param_2);
  
  // Store global pointer for later use
  uVar1 = DAT_00e44620;
  
  // Set vtable pointers for multiple inheritance
  *this = &PTR_FUN_00d81288;          // Primary vtable at offset 0x00
  this[0xf] = &PTR_LAB_00d81278;      // Secondary vtable at offset 0x3C
  this[0x12] = &PTR_LAB_00d81274;     // Tertiary vtable at offset 0x48
  
  // Initialize short fields (likely flags or counters)
  *(undefined2 *)(this + 0x19) = 0;   // +0x64: short field
  *(undefined2 *)((int)this + 0x66) = 0; // +0x66: short field
  *(undefined2 *)(this + 0x1b) = 0;   // +0x6C: short field
  *(undefined2 *)((int)this + 0x6e) = 0; // +0x6E: short field
  
  // Set debug sentinel values (will be overwritten later)
  this[0x1f] = 0xbadbadba;            // +0x7C: debug marker
  this[0x20] = 0xbeefbeef;            // +0x80: debug marker
  this[0x26] = 0xbadbadba;            // +0x98: debug marker
  this[0x27] = 0xbeefbeef;            // +0x9C: debug marker
  
  // Assign global pointers
  this[0x16] = uVar1;                 // +0x58: some global pointer
  this[0x1c] = DAT_00d5ccf8;          // +0x70: another global pointer
  
  // Initialize various fields to zero
  this[0x14] = 0;                     // +0x50
  this[0x15] = 0;                     // +0x54
  this[0x1e] = 0;                     // +0x78
  this[0x17] = 1;                     // +0x5C: set to 1 (maybe active flag)
  this[0x22] = 0;                     // +0x88
  this[0x21] = 0;                     // +0x84
  this[0x20] = 0;                     // +0x80: overwrite sentinel
  this[0x1f] = 0;                     // +0x7C: overwrite sentinel
  this[0x23] = 0;                     // +0x8C
  
  // Assign more global data
  this[0x24] = DAT_00e4458c;          // +0x90
  this[0x25] = DAT_00d5779c;          // +0x94
  
  // Clear sentinel region again
  uVar1 = DAT_00d5c454;
  this[0x29] = 0;                     // +0xA4
  this[0x28] = 0;                     // +0xA0
  this[0x27] = 0;                     // +0x9C: overwrite sentinel
  this[0x26] = 0;                     // +0x98: overwrite sentinel
  this[0x18] = 0;                     // +0x60
  this[0x1a] = 0;                     // +0x68
  
  // Final assignments
  this[0x2a] = uVar1;                 // +0xA8: from DAT_00d5c454
  uVar1 = DAT_00d5d7b8;
  this[0x2c] = 0;                     // +0xB0
  this[0x2b] = uVar1;                 // +0xAC: from DAT_00d5d7b8
  
  return this;
}