// Xbox PDB: EARS_Modules_WitnessComponent_WitnessComponent
// FUNC_NAME: CrimeSceneManager::constructor
undefined4 * __thiscall CrimeSceneManager::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  uVar1 = DAT_00e4475c;
  this[3] = param_2;                    // +0x0C: some parameter/context pointer
  this[2] = 0;                           // +0x08: state/count = 0
  this[1] = 0x21;                        // +0x04: flags/size = 0x21
  this[5] = 0;                           // +0x14: counter
  this[4] = &PTR_LAB_00d58278;           // +0x10: vtable base
  this[7] = &PTR___purecall_00d696a0;    // +0x1C: purecall placeholder
  *this = &PTR_FUN_00d696e0;            // +0x00: vtable
  this[4] = &PTR_LAB_00d696cc;          // +0x10: update vtable entry
  this[7] = &PTR_LAB_00d696c4;          // +0x1C: vtable entry
  this[10] = 0;                          // +0x28: count
  this[0xb] = 0xbadbadba;               // +0x2C: sentinel / magic 1
  this[0xc] = 0xbeefbeef;               // +0x30: sentinel / magic 2
  this[0xd] = 0xeac15a55;               // +0x34: sentinel / magic 3
  this[0xe] = 0x91100911;               // +0x38: sentinel / magic 4
  this[0xf] = 0;                         // +0x3C: pointer data
  this[0x10] = 0;                        // +0x40: pointer data
  this[0x11] = 0;                        // +0x44: pointer data
  this[0x15] = uVar1;                    // +0x54: some global/dat
  this[0x16] = DAT_00d58cbc;            // +0x58: global
  this[0x17] = DAT_00d5ccf8;            // +0x5C: global
  this[0x18] = DAT_00d5eee4;            // +0x60: global
  this[0x19] = 0;                        // +0x64: entry count
  this[0x1a] = 0;                        // +0x68: entry count
  this[0x1b] = 0;                        // +0x6C: entry count
  this[0x1c] = 0;                        // +0x70: entry count
  this[0x1d] = 0;                        // +0x74: entry count
  FUN_004086b0(&DAT_0120e93c,0x7fff);    // some hash/string init
  FUN_00408240(&DAT_0112af60,"iMsgWitnessedPlayerCrime"); // register message type
  return this;
}