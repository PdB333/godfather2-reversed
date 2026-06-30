// FUNC_NAME: GameGlobals::initialize
undefined4 * GameGlobals::initialize(void)
{
  FUN_006126d0(); // likely memory pool or subsystem init

  _DAT_01219b40 = 0;  // +0x00? first field
  _DAT_01219b44 = 0;  // +0x04
  _DAT_01219b48 = 0;  // +0x08
  _DAT_01219b34 = 0;  // +0xFC? (before start)
  _DAT_01219b4c = DAT_00e2b1a4; // +0x10, initialize to some global constant (likely 0x7FFFFFFF or -1)
  _DAT_01219b24 = 0;  // +0xE0? (before start)
  _DAT_01219b28 = 0;  // +0xE4
  DAT_01219a70 = &PTR_LAB_00e386a8; // vtable pointer or class static table
  _DAT_01219b50 = DAT_00e2b1a4; // +0x14
  uRam01219b54 = 0;  // +0x18
  uRam01219b58 = 0;  // +0x1C
  uRam01219b5c = 0;  // +0x20
  _DAT_01219b60 = 0;  // +0x24
  uRam01219b64 = DAT_00e2b1a4; // +0x28
  uRam01219b68 = 0;  // +0x2C
  uRam01219b6c = 0;  // +0x30
  _DAT_01219b70 = 0;  // +0x34
  uRam01219b74 = 0;  // +0x38
  uRam01219b78 = DAT_00e2b1a4; // +0x3C
  uRam01219b7c = 0;  // +0x40
  _DAT_01219b80 = 0;  // +0x44
  uRam01219b84 = 0;  // +0x48
  uRam01219b88 = 0;  // +0x4C
  uRam01219b8c = DAT_00e2b1a4; // +0x50
  _DAT_01219b90 = DAT_00e2b1a4; // +0x54
  uRam01219b94 = 0;  // +0x58
  uRam01219b98 = 0;  // +0x5C
  uRam01219b9c = 0;  // +0x60
  _DAT_01219ba0 = 0;  // +0x64
  uRam01219ba4 = DAT_00e2b1a4; // +0x68
  uRam01219ba8 = 0;  // +0x6C
  uRam01219bac = 0;  // +0x70
  _DAT_01219bb0 = 0;  // +0x74
  uRam01219bb4 = 0;  // +0x78
  uRam01219bb8 = DAT_00e2b1a4; // +0x7C
  uRam01219bbc = 0;  // +0x80
  _DAT_01219bc0 = 0;  // +0x84
  uRam01219bc4 = 0;  // +0x88
  uRam01219bc8 = 0;  // +0x8C
  uRam01219bcc = DAT_00e2b1a4; // +0x90
  return &DAT_01219a70; // return pointer to class instance
}