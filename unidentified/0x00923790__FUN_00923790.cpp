// FUNC_NAME: SomeClass::getSomeValue
undefined4 __fastcall SomeClass::getSomeValue(int thisPtr)
{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *(uint *)(thisPtr + 0x58); // +0x58: some index/state
  uVar2 = 0;
  if (((uVar1 != 0) || (2 < *(uint *)(thisPtr + 0x54))) && (uVar1 < 5)) {
    uVar2 = *(undefined4 *)((&PTR_DAT_00e564f8)[uVar1 * 2] + *(int *)(thisPtr + 0x54) * 100);
  }
  return uVar2;
}