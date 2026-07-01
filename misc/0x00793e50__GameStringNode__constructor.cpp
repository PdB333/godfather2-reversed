// FUNC_NAME: GameStringNode::constructor
undefined4 * __thiscall GameStringNode::constructor(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  FUN_0064cc90(); // likely base class constructor or memory initialization
  *this = &PTR_LAB_00d6a154; // vtable pointer assignment
  _strncpy((char *)(this + 8), name, 0x3f); // copy name string, max 63 chars (+0x20 offset)
  this[1] = param3; // +0x04
  this[3] = param4; // +0x0C
  this[2] = param5; // +0x08
  this[4] = 0; // +0x10
  this[5] = 0; // +0x14
  this[6] = 0; // +0x18
  this[7] = 0; // +0x1C
  this[0x1c] = DAT_012059ec; // +0x70, link to previous node in global list
  DAT_012059ec = this; // update global head pointer to this node
  return this;
}