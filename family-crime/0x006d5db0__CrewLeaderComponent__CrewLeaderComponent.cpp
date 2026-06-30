// FUNC_NAME: CrewLeaderComponent::CrewLeaderComponent
// Address: 0x006d5db0
// Role: Constructor for CrewLeaderComponent, initializes vtable pointers and zeroes fields.

undefined4 * __thiscall CrewLeaderComponent::CrewLeaderComponent(undefined4 *this, undefined4 arg)
{
  // Call base class constructor (likely Sentient or Component base)
  FUN_0046c590(arg);

  // Set primary vtable pointer
  *this = &PTR_FUN_00d5f42c;

  // Set secondary vtable pointers (interface implementations)
  this[0xf] = &PTR_LAB_00d5f41c;  // +0x3C
  this[0x12] = &PTR_LAB_00d5f418; // +0x48

  // Zero out various fields
  this[0x14] = 0;                 // +0x50
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (2 bytes)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (2 bytes)
  this[0x19] = 0;                 // +0x64
  this[0x18] = 0;                 // +0x60
  this[0x17] = 0;                 // +0x5C
  this[0x16] = 0;                 // +0x58
  this[0x1a] = 0;                 // +0x68

  return this;
}