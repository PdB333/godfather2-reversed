// FUNC_NAME: Player::constructor
undefined4 * __thiscall Player::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046e6b0(param_2,0x4000);
  *this = &PTR_FUN_00d78918;
  this[0xf] = &PTR_LAB_00d78908;
  this[0x12] = &PTR_LAB_00d78904;
  this[0x14] = &PTR_LAB_00d78900;
  this[0x15] = &PTR_LAB_00d788a0;
  this[0x16] = &PTR_LAB_00d78838;
  this[0x67] = 0xbadbadba;
  this[0x68] = 0xbeefbeef;
  this[0x69] = 0xeac15a55;
  this[0x6a] = 0x91100911;
  this[0x6c] = 0xbeefbeef;
  this[0x6b] = 0xbadbadba;
  this[0x6d] = 0xeac15a55;
  this[0x6e] = 0x91100911;
  this[0x70] = 0xbeefbeef;
  this[0x6f] = 0xbadbadba;
  this[0x71] = 0xeac15a55;
  this[0x72] = 0x91100911;
  this[0x73] = 0;
  *(undefined2 *)(this + 0x74) = 0;
  *(undefined2 *)((int)this + 0x1d2) = 0;
  this[0x75] = 0;
  *(undefined2 *)(this + 0x76) = 0;
  *(undefined2 *)((int)this + 0x1da) = 0;
  this[0x77] = 0;
  *(undefined2 *)(this + 0x78) = 0;
  *(undefined2 *)((int)this + 0x1e2) = 0;
  this[0x79] = 0;
  this[0x7c] = 0xfe16702f;
  FUN_00481530();
  this[0x61] = DAT_00d5d7b8;
  this[0x62] = _DAT_00d5780c;
  this[99] = DAT_00e445ac;
  this[0x60] = 0;
  this[0x66] = 0;
  this[0x7a] = 0xffffffff;
  this[0x7b] = 0;
  this[100] = 0;
  this[0x65] = 0;
  FUN_008a0d20(this);
  if (*(char *)(DAT_01129914 + 0xd3) != '\0') {
    FUN_00408680(&DAT_012069c4);
  }
  return this;
}