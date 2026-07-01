// FUNC_NAME: GodfatherGameManager::constructor

undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 initData)
{
  uint globalVal;

  // Call base class constructor or initialization function
  FUN_0046c590(initData);

  // Fetch global constant value (likely -1 or 0xFFFFFFFF)
  globalVal = _DAT_00d5780c;

  // Set primary vtable pointer
  *this = &PTR_FUN_00d73158;

  // Set secondary vtable pointers (multiple inheritance)
  this[0xf] = &PTR_LAB_00d73148;  // +0x3C
  this[0x12] = &PTR_LAB_00d73144; // +0x48

  // Initialize various fields to 0
  this[0x14] = 0;  // +0x50
  this[0x15] = 0;  // +0x54
  this[0x16] = 0;  // +0x58
  this[0x17] = 0;  // +0x5C
  this[0x18] = 0;  // +0x60
  this[0x19] = 0;  // +0x64
  this[0x1e] = 0;  // +0x78
  this[0x1f] = 0;  // +0x7C
  this[0x27] = 0;  // +0x9C

  // Set byte fields (flags, indices, etc.)
  *(byte *)(this + 0x23) = 0;   // +0x8C
  *(byte *)((int)this + 0x8d) = 0; // +0x8D
  *(byte *)((int)this + 0x8e) = 0; // +0x8E

  // Initialize fields with global constant (e.g., -1 for invalid handles)
  this[0x20] = globalVal;  // +0x80
  this[0x21] = globalVal;  // +0x84
  this[0x1c] = globalVal;  // +0x70
  this[0x1d] = globalVal;  // +0x74

  // Set a count to 1 (e.g., reference count, active state)
  this[0x26] = 1;  // +0x98

  // Initialize tracking fields
  this[0x1a] = 0;  // +0x68
  this[0x1b] = 0;  // +0x6C

  // Set byte fields to 0xFF (invalid/empty state)
  *(byte *)(this + 0x22) = 0xff;      // +0x88
  *(byte *)((int)this + 0x89) = 0xff; // +0x89
  *(byte *)((int)this + 0x8a) = 0xff; // +0x8A
  *(byte *)((int)this + 0x8b) = 0xff; // +0x8B
  *(byte *)((int)this + 0x8f) = 0xff; // +0x8F

  // Zero out additional fields
  this[0x24] = 0;  // +0x90
  this[0x25] = 0;  // +0x94

  return this;
}