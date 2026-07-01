// FUNC_NAME: WeaponData::getFireRate
undefined4 __fastcall WeaponData::getFireRate(int this)
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0x14;
  if (*(uint *)(this + 8) < DAT_011307fc) {
    iVar1 = *(int *)(DAT_011307f8 + *(uint *)(this + 8) * 8);
    if (iVar1 == 0x3d26cff9) {
      uVar2 = 4000;
    }
    else {
      if (iVar1 == 0x45c2f636) {
        return 3;
      }
      if (iVar1 == 0x7116917a) {
        return 2000;
      }
    }
  }
  return uVar2;
}