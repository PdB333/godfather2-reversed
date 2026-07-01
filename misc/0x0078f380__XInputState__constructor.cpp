// FUNC_NAME: XInputState::constructor
undefined4 * __thiscall XInputState::constructor(XInputState *this, undefined4 param_2)

{
  FUN_0078f840(param_2); // likely base class or subcomponent init
  this->vtable = &PTR_FUN_00d69c24;
  this[0xf] = &PTR_LAB_00d69c14;     // +0x3C - vtable or interface ptr
  this[0x12] = &PTR_LAB_00d69c10;    // +0x48 - vtable or interface ptr  
  this[0x14] = &PTR_LAB_00d69bf8;    // +0x50 - vtable or interface ptr
  // 8 controller slots initialized with sentinel markers
  this[0x2d] = 0xbadbadba;  // +0xB4 - slot 0 flags
  this[0x31] = 0xbadbadba;  // +0xC4 - slot 1 flags
  this[0x35] = 0xbadbadba;  // +0xD4 - slot 2 flags
  this[0x39] = 0xbadbadba;  // +0xE4 - slot 3 flags
  this[0x3d] = 0xbadbadba;  // +0xF4 - slot 4 flags
  this[0x41] = 0xbadbadba;  // +0x104 - slot 5 flags
  this[0x45] = 0xbadbadba;  // +0x114 - slot 6 flags
  this[0x49] = 0xbadbadba;  // +0x124 - slot 7 flags
  // 8 controller slots initialized with default state marker
  this[0x30] = 0x91100911;  // +0xC0 - slot 0 state.packetNumber
  this[0x34] = 0x91100911;  // +0xD0 - slot 1 state.packetNumber
  this[0x38] = 0x91100911;  // +0xE0 - slot 2 state.packetNumber
  this[0x3c] = 0x91100911;  // +0xF0 - slot 3 state.packetNumber
  this[0x40] = 0x91100911;  // +0x100 - slot 4 state.packetNumber
  this[0x44] = 0x91100911;  // +0x110 - slot 5 state.packetNumber
  this[0x48] = 0x91100911;  // +0x120 - slot 6 state.packetNumber
  this[0x4c] = 0x91100911;  // +0x130 - slot 7 state.packetNumber
  // 8 controller slots with connection status and battery info pairs
  this[0x2e] = 0xbeefbeef;  // +0xB8 - slot 0 connectionState
  this[0x2f] = 0xeac15a55;  // +0xBC - slot 0 batteryLevel
  this[0x32] = 0xbeefbeef;  // +0xC8 - slot 1 connectionState
  this[0x33] = 0xeac15a55;  // +0xCC - slot 1 batteryLevel
  this[0x36] = 0xbeefbeef;  // +0xD8 - slot 2 connectionState
  this[0x37] = 0xeac15a55;  // +0xDC - slot 2 batteryLevel
  this[0x3a] = 0xbeefbeef;  // +0xE8 - slot 3 connectionState
  this[0x3b] = 0xeac15a55;  // +0xEC - slot 3 batteryLevel
  this[0x3e] = 0xbeefbeef;  // +0xF8 - slot 4 connectionState
  this[0x3f] = 0xeac15a55;  // +0xFC - slot 4 batteryLevel
  this[0x42] = 0xbeefbeef;  // +0x108 - slot 5 connectionState
  this[0x43] = 0xeac15a55;  // +0x10C - slot 5 batteryLevel
  this[0x46] = 0xbeefbeef;  // +0x118 - slot 6 connectionState
  this[0x47] = 0xeac15a55;  // +0x11C - slot 6 batteryLevel
  this[0x4a] = 0xbeefbeef;  // +0x128 - slot 7 connectionState
  this[0x4b] = 0xeac15a55;  // +0x12C - slot 7 batteryLevel
  return this;
}