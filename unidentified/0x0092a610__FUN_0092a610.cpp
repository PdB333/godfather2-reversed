// FUNC_NAME: SomeManager::constructor
undefined4 * __fastcall SomeManager::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  this[3] = 0;  // +0x0C: some field
  this[1] = 0;  // +0x04: some field
  this[2] = 0;  // +0x08: some field
  this[4] = 0;  // +0x10: some field
  this[5] = 0;  // +0x14: some field
  this[6] = &PTR_LAB_00d88594;  // +0x18: vtable or pointer
  _DAT_011304f0 = this;  // global singleton pointer
  *this = &PTR_FUN_00d8859c;  // +0x00: vtable pointer
  this[6] = &PTR_LAB_00d88598;  // +0x18: another pointer
  this[7] = 0;  // +0x1C: some field
  this[9] = 0;  // +0x24: some field
  this[0xb] = 0;  // +0x2C: some field
  this[0xc] = 0;  // +0x30: some field
  this[0xe] = 0;  // +0x38: some field
  this[0xf] = 0;  // +0x3C: some field
  this[0x10] = 0;  // +0x40: some field
  this[0x11] = 0;  // +0x44: some field
  this[0x12] = 0;  // +0x48: some field
  uVar1 = FUN_009c8e80(0x20);  // allocate 0x20 bytes
  this[8] = uVar1;  // +0x20: pointer to allocated buffer
  puVar2 = (undefined1 *)FUN_009c8e80(0x20);  // allocate another 0x20 bytes
  this[10] = puVar2;  // +0x28: pointer to allocated buffer
  *puVar2 = 0;  // clear first byte
  *(undefined1 *)this[8] = 0;  // clear first byte of first buffer
  return this;
}