// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(undefined4 *this, undefined4 param_2)

{
  FUN_006c9760(param_2,_DAT_00d5cf70);
  *this = &PTR_FUN_00d5f6a4;
  this[2] = &PTR_LAB_00d5f69c;
  FUN_006dc940();
  this[0xa9] = this[0x38]; // +0x2A4: copy from some state
  this[0x98] = 0;          // +0x260: clear
  this[0xaa] = this[0x39]; // +0x2A8: copy from another state
  this[0x99] = 0;          // +0x264: clear
  this[0x9a] = 0;          // +0x268: clear
  this[0xa1] = 0;          // +0x284: clear
  this[0xa3] = 0;          // +0x28C: clear
  this[0xa5] = 0;          // +0x294: clear
  this[0xa6] = 0;          // +0x298: clear
  this[0xa7] = 0;          // +0x29C: clear
  this[0xa8] = 0;          // +0x2A0: clear
  this[0xac] = 0;          // +0x2B0: clear
  this[0xad] = 0;          // +0x2B4: clear
  this[0xae] = 0;          // +0x2B8: clear
  this[0xaf] = 0;          // +0x2BC: clear
  this[0xb0] = 0;          // +0x2C0: clear
  this[0xb1] = 0;          // +0x2C4: clear
  this[0xb2] = 0;          // +0x2C8: clear
  this[0xb3] = 0;          // +0x2CC: clear
  this[0x88] = 0;          // +0x220: clear
  *(undefined1 *)(this + 0xa2) = 0; // +0x288: byte clear
  *(undefined1 *)(this + 0xa4) = 0; // +0x290: byte clear
  *(undefined1 *)(this + 0xab) = 0; // +0x2AC: byte clear
  this[0xb4] = 0;          // +0x2D0: clear
  this[0x8b] = 0;          // +0x22C: clear
  this[0x8a] = 0;          // +0x228: clear
  this[0x89] = 0;          // +0x224: clear
  this[0x8e] = 0;          // +0x238: clear
  this[0x8d] = 0;          // +0x234: clear
  this[0x8c] = 0;          // +0x230: clear
  this[0x91] = 0;          // +0x244: clear
  this[0x90] = 0;          // +0x240: clear
  this[0x8f] = 0;          // +0x23C: clear
  this[0x94] = 0;          // +0x250: clear
  this[0x93] = 0;          // +0x24C: clear
  this[0x92] = 0;          // +0x248: clear
  this[0x97] = 0;          // +0x25C: clear
  this[0x96] = 0;          // +0x258: clear
  this[0x95] = 0;          // +0x254: clear
  this[0x9d] = 0;          // +0x274: clear
  this[0x9c] = 0;          // +0x270: clear
  this[0x9b] = 0;          // +0x26C: clear
  this[0xa0] = 0;          // +0x280: clear
  this[0x9f] = 0;          // +0x27C: clear
  this[0x9e] = 0;          // +0x278: clear
  return this;
}