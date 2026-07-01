// FUNC_NAME: Player::Player
undefined4* __thiscall Player::Player(undefined4* this, undefined4 param_2)
{
  undefined4 g_someDefaultSpeed1;  // DAT_00d8b2ac
  undefined4 g_someDefaultSpeed2;  // DAT_00d8b2a8
  undefined4 g_anotherDefault;    // from DAT_00d5780c etc.
  undefined4 localVar;

  // Call base class constructor (likely Entity or Character)
  BaseClass::Constructor(param_2);

  // Set vtable pointers (primary and secondary interfaces)
  this[0x0] = &VTable_Player;          // +0x00: primary vtable
  this[0xF] = &VTable_Secondary1;      // +0x3C: secondary vtable (interface)
  this[0x12] = &VTable_Secondary2;     // +0x48: tertiary vtable

  // Initialize fields to default global constants
  this[0x14] = 0;                      // +0x50: some counter/flag
  *(uint16*)((uint)this + 0x54) = 0;   // +0x54: halfword field
  this[0x16] = g_someDefaultSpeed1;    // +0x58: default speed 1
  this[0x17] = g_someDefaultSpeed1;    // +0x5C: same default copy
  this[0x18] = DAT_00d8b2a4;          // +0x60: another default (maybe acceleration)
  this[0x19] = DAT_00d5f378;          // +0x64: default health?
  this[0x1A] = DAT_00e446f4;          // +0x68: default max health?
  this[0x1B] = 0;                      // +0x6C: some counter
  this[0x1C] = DAT_00d8b2a0;          // +0x70: default value (turn speed?)
  this[0x1D] = DAT_00d8b29c;          // +0x74
  this[0x1E] = DAT_00d8b298;          // +0x78
  this[0x1F] = _DAT_00d5780c;         // +0x7C: constant used twice
  this[0x20] = DAT_00d8b2a8;          // +0x80
  this[0x21] = DAT_00d75ca0;          // +0x84
  this[0x22] = _DAT_00d5780c;         // +0x88: same constant again
  this[0x23] = 0;                      // +0x8C
  *(uint16*)((uint)this + 0x90) = 0;  // +0x90: halfword
  *(uint16*)((uint)this + 0x92) = 0;  // +0x92: halfword
  this[0x25] = 0;                      // +0x94: dword
  *(uint16*)((uint)this + 0x98) = 0;  // +0x98: halfword
  *(uint16*)((uint)this + 0x9A) = 0;  // +0x9A: halfword
  *(uint8*)((uint)this + 0x9C) = 0;   // +0x9C: byte

  // If a global pointer exists, copy 0x8000 bytes into the secondary interface area (offset +0x3C)
  if (g_DefaultAnimationDataPtr != 0) {
    CopyMemory(this + 0xF, g_DefaultAnimationDataPtr, 0x8000);
  }

  return this;
}