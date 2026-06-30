// FUNC_NAME: PlayerSM::PlayerSM
// Address: 0x006c9760
// Constructor for the PlayerSM (Player State Machine) base class. Initializes state fields,
// sets vtable pointers for multiple inheritance, and calls base object constructor and custom init.

undefined4 * __thiscall PlayerSM::PlayerSM(undefined4 *this, undefined4 param2, undefined4 param3)
{
  // Call base class constructor (likely EARSObject or SimObject, takes an owner pointer)
  FUN_00473950(param2);

  // Set vtable pointers: first for derived class, second for secondary interface
  *this = &PTR_FUN_00d5f060;            // +0x00: primary vtable
  this[2] = &PTR_LAB_00d5f058;          // +0x08: secondary vtable

  // Clear all state machine fields to default values
  this[0x19] = 0;                       // +0x64: e.g., action timer
  this[0x1A] = 0;                       // +0x68: another timer or counter
  this[0x1B] = 0xFFFFFFFF;              // +0x6C: current state index (initialized to -1/invalid)
  this[0x1C] = 0;                       // +0x70
  this[0x1D] = 0;                       // +0x74
  this[0x1E] = 0;                       // +0x78
  *(uint8_t *)((uint8_t *)this + 0x7C) = 0; // +0x7C: byte flag
  this[0x20] = 0;                       // +0x80
  this[0x21] = 0;                       // +0x84
  this[0x22] = 0;                       // +0x88
  this[0x23] = 0;                       // +0x8C
  this[0x24] = 0;                       // +0x90
  this[0x25] = 0;                       // +0x94
  this[0x26] = 0;                       // +0x98
  this[0x27] = 0;                       // +0x9C
  this[0x28] = 0;                       // +0xA0
  this[0x29] = 0;                       // +0xA4
  this[0x2A] = 0;                       // +0xA8
  this[0x2B] = 0;                       // +0xAC

  // Call specialised initialization with owner and extra parameter
  FUN_006c9660(param2, param3);         // likely 'initStateMachine(owner, extra)'

  return this;
}