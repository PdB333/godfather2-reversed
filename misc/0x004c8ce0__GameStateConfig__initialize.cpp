// FUNC_NAME: GameStateConfig::initialize
undefined4 * GameStateConfig::initialize(undefined4 *this, undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = DAT_00e2eff4;
  *this = 0;
  *(undefined1 *)(this + 1) = 0;
  // +0x290: some flag offset
  this[0xa4] = 0;
  // +0x294, +0x298, +0x29c: color/state values
  this[0xa5] = uVar1;
  this[0xa6] = uVar1;
  this[0xa7] = uVar1;
  uVar1 = DAT_00e2b1a4;
  // +0x2a0, +0x2a4: more state values
  this[0xa8] = DAT_00e2b1a4;
  this[0xa9] = uVar1;
  this[0xaa] = 0;
  this[0xab] = 0;
  // +0x2c8: timeout value (96000ms)
  this[0xb2] = 96000;
  // +0x2b0: enabled flag
  this[0xac] = 1;
  // +0x2c0: bitmask
  this[0xb0] = 0x91100911;
  // +0x2b4, 0x2b8, 0x2bc, 0x2c0: magic values
  this[0xad] = 0xbadbadba;
  this[0xae] = 0xbeefbeef;
  this[0xaf] = 0xeac15a55;
  *(undefined1 *)(this + 0xb1) = 0;
  FUN_004c8c10();
  puVar3 = this + 0xb3;
  for (iVar2 = 0x2c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_2;
    param_2 = param_2 + 1;
    puVar3 = puVar3 + 1;
  }
  _memset(this + 4,0,0x280); // Clear data block at +0x10 to +0x290
  uVar1 = FUN_004dafd0(this + 0xb7); // Likely allocate/create resource
  this[2] = uVar1;
  uVar1 = FUN_004dafd0(this + 0xbf);
  this[3] = uVar1;
  return this;
}