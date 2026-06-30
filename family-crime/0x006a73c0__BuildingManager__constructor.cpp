// FUNC_NAME: BuildingManager::constructor
undefined4 * __thiscall BuildingManager_constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (possibly EARS::EntityManager or similar)
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5d840;  // +0x00 vtable
  
  // Initialize building pointers/arrays (offset 0x3C = 15 * 4)
  this[0xf] = &PTR_LAB_00d5d830;  // +0x3C building list pointer?
  this[0x12] = &PTR_LAB_00d5d82c; // +0x48 another building resource pointer?
  
  // Zero out building counters and flags (offsets 0x70 to 0x8C)
  this[0x1c] = 0;  // +0x70 building count
  this[0x14] = 0;  // +0x50 some state flag
  this[0x1d] = 0;  // +0x74 building index counter?
  this[0x15] = 0;  // +0x54 
  this[0x1e] = 0;  // +0x78
  this[0x16] = 0;  // +0x58
  this[0x1f] = 0;  // +0x7C
  this[0x17] = 0;  // +0x5C
  this[0x20] = 0;  // +0x80
  this[0x18] = 0;  // +0x60
  this[0x21] = 0;  // +0x84
  this[0x19] = 0;  // +0x64
  this[0x22] = 0;  // +0x88
  this[0x1a] = 0;  // +0x68
  this[0x23] = 0;  // +0x8C
  this[0x1b] = 0;  // +0x6C
  
  return this;
}