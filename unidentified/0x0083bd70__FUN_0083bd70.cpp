// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(undefined4 *this, undefined4 param2, undefined4 param3, undefined4 param4, float param5, undefined4 param6, undefined4 param7, undefined4 param8)
{
  int iVar1;
  undefined4 *puVar2;
  
  this[2] = param2;
  this[4] = param4;
  this[6] = param6;
  this[3] = param3;
  this[8] = param8;
  *this = &PTR_FUN_00d742f0; // vtable pointer
  this[1] = 0; // +0x04: some pointer/flag
  this[5] = param5; // +0x14: float value
  this[7] = param7; // +0x1C: some value
  puVar2 = this + 10; // +0x28: start of array
  iVar1 = 0xff; // 255 iterations
  do {
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2 = puVar2 + 3;
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  // Clear 256 * 3 = 768 dwords (3072 bytes) starting at offset +0x28
  if ((*(uint *)(this[2] + 0xa8) >> 10 & 1) != 0) {
    param5 = param5 * _DAT_00d742dc; // global multiplier
  }
  this[9] = param5; // +0x24: final float value
  return;
}