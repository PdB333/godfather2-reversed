// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  uVar1 = DAT_00d5eeec;
  this[6] = _DAT_00d5780c;
  this[9] = uVar1;
  this[3] = param_2;
  this[2] = 0;
  this[1] = 0x21;
  *this = &PTR_FUN_00d6990c; // vtable pointer
  this[4] = 0;
  this[5] = 0;
  this[0xb] = 0;
  this[0xc] = 0;
  this[0xd] = 0;
  this[0xf] = 0;
  this[0x10] = 0;
  this[0x11] = 0;
  this[0x12] = 0;
  this[0x13] = 0;
  this[0x14] = 0;
  this[7] = DAT_00e44594;
  this[8] = 0;
  this[10] = DAT_00d5842c;
  this[0xe] = DAT_00d5ccf8;
  this[0x15] = 0;
  this[0x16] = 0;
  this[0x17] = 0;
  this[0x18] = 0;
  this[0x19] = 0;
  this[0x1a] = 0;
  this[0x1b] = 0;
  this[0x1c] = 0;
  this[0x1d] = 0;
  *(undefined2 *)(this + 0x1e) = 0;
  *(undefined2 *)((int)this + 0x7a) = 0;
  this[0x1f] = 0;
  *(undefined2 *)(this + 0x20) = 0;
  *(undefined2 *)((int)this + 0x82) = 0;
  this[0x21] = 0xbadbadba; // sentinel value
  this[0x22] = 0xbeefbeef; // sentinel value
  this[0x23] = 0xeac15a55; // sentinel value
  this[0x24] = 0x91100911; // sentinel value
  this[0x25] = 0xbadbadba;
  this[0x26] = 0xbeefbeef;
  this[0x27] = 0xeac15a55;
  this[0x28] = 0x91100911;
  this[0x29] = 0;
  this[0x2a] = 0;
  this[0x31] = 0;
  this[0x32] = 0;
  *(undefined1 *)(this + 0x39) = 0;
  this[0x2b] = 0;
  this[0x2c] = 0;
  this[0x33] = 0;
  this[0x35] = 0;
  this[0x34] = 0;
  this[0x30] = 0;
  this[0x2f] = 0;
  this[0x2e] = 0;
  this[0x38] = 0;
  this[0x37] = 0;
  this[0x36] = 0;
  uVar1 = DAT_00e44718;
  this[0x3a] = 0;
  this[0x3b] = 0;
  this[0x2d] = uVar1;
  if (DAT_0112afb0 != 0) {
    FUN_00408900(this,&DAT_0112afb0,0x8000); // copy 0x8000 bytes from global buffer
  }
  if (DAT_0112afa8 != 0) {
    FUN_00408900(this,&DAT_0112afa8,0x8000); // copy 0x8000 bytes from another global buffer
  }
  return this;
}