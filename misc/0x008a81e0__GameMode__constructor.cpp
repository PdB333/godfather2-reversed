// FUNC_NAME: GameMode::constructor
undefined4 * __thiscall GameMode::constructor(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  FUN_0064cc90(); // likely base constructor or memory init
  *this = &PTR_LAB_00d79c50; // vtable pointer for GameMode
  _strncpy((char *)(this + 8), name, 0x3f); // +0x20 name buffer (63 chars max)
  this[1] = param3; // +0x04 game mode type/id
  this[3] = param4; // +0x0C unknown parameter
  this[2] = param5; // +0x08 unknown parameter
  this[4] = 0; // +0x10 pointer or count
  this[5] = 0; // +0x14 pointer or count
  this[6] = 0; // +0x18 pointer or count
  this[7] = 0; // +0x1C pointer or count
  this[0x1c] = DAT_012059ec; // +0x70 linked list previous pointer (DAT_012059ec is head of list)
  DAT_012059ec = this; // update head pointer to this
  return this;
}