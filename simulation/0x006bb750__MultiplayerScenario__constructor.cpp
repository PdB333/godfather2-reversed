// FUNC_NAME: MultiplayerScenario::constructor
undefined4 * __thiscall MultiplayerScenario::constructor(undefined4 *this, undefined4 someParameter)
{
  // Call base class constructor with the parameter
  FUN_006bd1d0(someParameter); // likely BaseNetworkObject::initialize or similar

  // Set up vtable pointers (multiple inheritance)
  this[0x20] = &PTR_LAB_00d5e71c;   // +0x80: base vtable pointer
  *this = &PTR_FUN_00d5e76c;        // +0x00: primary vtable pointer
  this[0xf] = &PTR_LAB_00d5e75c;    // +0x3C: second vtable pointer
  this[0x12] = &PTR_LAB_00d5e758;   // +0x48: third vtable pointer
  this[0x20] = &PTR_LAB_00d5e73c;   // +0x80: override base vtable (derived class)

  // Initialize member fields
  this[0x21] = 7;       // +0x84: slot count or capacity
  this[0x24] = 0;       // +0x90
  this[0x25] = 0;       // +0x94
  this[0x26] = 0;       // +0x98
  this[0x27] = 0;       // +0x9C
  this[0x22] = 0;       // +0x88
  this[0x23] = 0;       // +0x8C
  this[0x28] = 0;       // +0xA0
  this[0x29] = 0;       // +0xA4
  this[0x2a] = 0;       // +0xA8
  this[0x2b] = 0;       // +0xAC
  this[0x2c] = 0;       // +0xB0
  this[0x2d] = 0;       // +0xB4
  this[0x2f] = 0;       // +0xBC
  this[0x32] = 0;       // +0xC8

  // Initialize array of player slot data (10 groups of: int + two shorts)
  // Each group at offsets: 0xC0, 0xCC, 0xD4, 0xE0, 0xEC, 0xF8, 0x104, 0x110, 0x11C, 0x128
  *(undefined2 *)(this + 0x30) = 0;        // +0xC0: low word of first slot int
  *(undefined2 *)((int)this + 0xc2) = 0;   // +0xC2: high word
  *(undefined2 *)(this + 0x33) = 0;        // +0xCC: low word of second slot int
  *(undefined2 *)((int)this + 0xce) = 0;   // +0xCE: high word
  this[0x35] = 0;                           // +0xD4: third slot int
  *(undefined2 *)(this + 0x36) = 0;         // +0xD8: low word
  *(undefined2 *)((int)this + 0xda) = 0;   // +0xDA: high word
  this[0x38] = 0;                           // +0xE0: fourth slot int
  *(undefined2 *)(this + 0x39) = 0;         // +0xE4: low word
  *(undefined2 *)((int)this + 0xe6) = 0;   // +0xE6: high word
  this[0x3b] = 0;                           // +0xEC: fifth slot int
  *(undefined2 *)(this + 0x3c) = 0;         // +0xF0: low word
  *(undefined2 *)((int)this + 0xf2) = 0;   // +0xF2: high word
  this[0x3e] = 0;                           // +0xF8: sixth slot int
  *(undefined2 *)(this + 0x3f) = 0;         // +0xFC: low word
  *(undefined2 *)((int)this + 0xfe) = 0;   // +0xFE: high word
  this[0x41] = 0;                           // +0x104: seventh slot int
  *(undefined2 *)(this + 0x42) = 0;         // +0x108: low word
  *(undefined2 *)((int)this + 0x10a) = 0;  // +0x10A: high word
  this[0x44] = 0;                           // +0x110: eighth slot int
  *(undefined2 *)(this + 0x45) = 0;         // +0x114: low word
  *(undefined2 *)((int)this + 0x116) = 0;  // +0x116: high word
  this[0x47] = 0;                           // +0x11C: ninth slot int
  *(undefined2 *)(this + 0x48) = 0;         // +0x120: low word
  *(undefined2 *)((int)this + 0x122) = 0;  // +0x122: high word
  this[0x4a] = 0;                           // +0x128: tenth slot int
  *(undefined2 *)(this + 0x4b) = 0;         // +0x12C: low word
  *(undefined2 *)((int)this + 0x12e) = 0;  // +0x12E: high word

  // Set default values for some fields
  this[0x2e] = 100;     // +0xB8: default timeout or max count
  this[0x31] = 0;       // +0xC4
  this[0x34] = 0;       // +0xD0
  this[0x37] = 0;       // +0xDC
  this[0x3a] = 0;       // +0xE8
  this[0x3d] = 0;       // +0xF4
  this[0x40] = 0;       // +0x100
  this[0x43] = 0;       // +0x10C
  this[0x46] = 0;       // +0x118
  this[0x49] = 0;       // +0x124

  return this;
}