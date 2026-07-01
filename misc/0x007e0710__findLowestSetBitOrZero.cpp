// FUNC_NAME: findLowestSetBitOrZero
uint __fastcall findLowestSetBitOrZero(int param_1)
{
  uint uVar1;
  
  uVar1 = 1;
  while ((uVar1 == 0 || ((*(uint *)(param_1 + 4) & uVar1) != uVar1))) {
    uVar1 = uVar1 * 2;
    if (0x40000000 < uVar1) {
      return 0;
    }
  }
  return uVar1;
}