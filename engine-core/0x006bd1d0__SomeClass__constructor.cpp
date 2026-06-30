// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)

{
  undefined4 *ptr;
  int size;
  
  FUN_0046c590(param_2);
  *this = &PTR_FUN_00d5ea20;
  this[0xf] = &PTR_LAB_00d5ea10;
  this[0x12] = &PTR_LAB_00d5ea0c;
  *(undefined1 *)(this + 0x14) = 0;
  this[0x15] = 0;
  this[0x16] = 0;
  this[0x17] = 0;
  this[0x18] = 0;
  this[0x19] = 0;
  this[0x1a] = 0;
  this[0x1b] = 0;
  this[0x1c] = 0;
  this[0x1d] = 0;
  this[0x1e] = 0;
  this[0x1f] = 0;
  // Grow a global array if needed (object registry)
  if (DAT_0112a6a4 == DAT_0112a6a8) {
    if (DAT_0112a6a8 == 0) {
      size = 1;
    }
    else {
      size = DAT_0112a6a8 * 2;
    }
    FUN_006bca00(size);
  }
  ptr = (undefined4 *)(DAT_0112a6a0 + DAT_0112a6a4 * 4);
  DAT_0112a6a4 = DAT_0112a6a4 + 1;
  if (ptr != (undefined4 *)0x0) {
    *ptr = this;
  }
  // Register event handlers
  FUN_004086b0(&DAT_01206778,0x8001);
  FUN_004086b0(&DAT_0120e93c,0x7fff);
  return this;
}