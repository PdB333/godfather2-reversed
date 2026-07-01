// FUNC_NAME: SomeClass::copyFromOrConstructor
undefined4 * __thiscall SomeClass::copyFromOrConstructor(undefined4 *this, int source)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  FUN_0081f9f0(source);
  *this = &PTR_LAB_00d736c0;
  this[0x13] = *(undefined4 *)(source + 0x4c);
  this[0x14] = *(undefined4 *)(source + 0x50);
  this[0x15] = *(undefined4 *)(source + 0x54);
  uVar1 = *(undefined4 *)(source + 100);
  uVar2 = *(undefined4 *)(source + 0x68);
  uVar3 = *(undefined4 *)(source + 0x6c);
  this[0x18] = *(undefined4 *)(source + 0x60);
  this[0x19] = uVar1;
  this[0x1a] = uVar2;
  this[0x1b] = uVar3;
  return this;
}