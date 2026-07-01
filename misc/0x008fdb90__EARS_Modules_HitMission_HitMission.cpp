// Xbox PDB: EARS_Modules_HitMission_HitMission
// FUNC_NAME: HitMission::constructor
undefined4 * __thiscall HitMission::constructor(HitMission *this,undefined4 param_2)

{
  // Call base class constructor or some initializer
  FUN_0046c590(param_2);
  
  // Set vtable pointer (likely HitMission vtable)
  this[0x14] = &PTR_LAB_00d5e214;
  // Set another vtable pointer (maybe multiple inheritance or interface)
  *this = &PTR_FUN_00d81624;
  this[0xf] = &PTR_LAB_00d81614;
  this[0x12] = &PTR_LAB_00d81610;
  this[0x14] = &PTR_LAB_00d815f8;
  
  // Initialize mission state variables
  this[0x15] = 0;   // +0x54: mission state or flags
  this[0x16] = 0;   // +0x58
  this[0x17] = 0;   // +0x5c
  *(undefined2 *)(this + 0x19) = 0;  // +0x64: short
  this[0x1a] = 0;   // +0x68
  this[0x1b] = 1;   // +0x6c: enabled/active flag
  this[0x1c] = 0;   // +0x70
  this[0x1d] = 0;   // +0x74
  
  // Clear some array of 32-bit values (0x24 to 0x28)
  this[0x27] = 0;   // +0x9c
  this[0x26] = 0;   // +0x98
  this[0x25] = 0;   // +0x94
  this[0x24] = 0;   // +0x90
  this[0x28] = 0;   // +0xa0
  
  // More zero initialization for what appears to be a tracking structure
  *(undefined2 *)(this + 0x29) = 0;  // +0xa4: short
  *(undefined2 *)((int)this + 0xa6) = 0;  // +0xa6: short
  this[0x2a] = 0;   // +0xa8
  *(undefined2 *)(this + 0x2b) = 0;  // +0xac: short
  *(undefined2 *)((int)this + 0xae) = 0;  // +0xae: short
  this[0x2c] = 0;   // +0xb0
  *(undefined2 *)(this + 0x2d) = 0;  // +0xb4: short
  *(undefined2 *)((int)this + 0xb6) = 0;  // +0xb6: short
  this[0x2e] = 0;   // +0xb8
  *(undefined2 *)(this + 0x2f) = 0;  // +0xbc: short
  *(undefined2 *)((int)this + 0xbe) = 0;  // +0xbe: short
  this[0x30] = 0;   // +0xc0
  *(undefined2 *)(this + 0x31) = 0;  // +0xc4: short
  *(undefined2 *)((int)this + 0xc6) = 0;  // +0xc6: short
  this[0x32] = 0;   // +0xc8
  this[0x33] = 0;   // +0xcc
  *(undefined2 *)(this + 0x34) = 0;  // +0xd0: short
  this[0x35] = 0;   // +0xd4
  this[0x36] = 0;   // +0xd8
  this[0x37] = 0;   // +0xdc
  this[0x38] = 0;   // +0xe0
  
  // More state initialization
  this[0x1e] = 0;   // +0x78
  this[0x20] = 0;   // +0x80
  *(undefined1 *)(this + 0x1f) = 0;  // +0x7c: byte
  *(undefined1 *)(this + 0x21) = 0;  // +0x84: byte
  this[0x22] = 0;   // +0x88
  *(undefined1 *)(this + 0x23) = 0;  // +0x8c: byte
  
  // Register for messages - likely "iMsgHitMissionComplete"
  FUN_00408240(&DAT_0112fee8,"iMsgHitMissionComplete");
  
  // Initialize some string buffer or hash table with 0x7fff size
  FUN_004086b0(&DAT_0120e93c,0x7fff);
  
  return this;
}