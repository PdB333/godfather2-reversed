// FUNC_NAME: CrimeScene::countActiveCrimes
int CrimeScene::countActiveCrimes(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *local_10;
  int local_c;
  int local_8;
  
  iVar1 = DAT_0112b6fc; // current crime type ID
  iVar4 = 0; // count of active crimes
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // offset to CrimeScene manager
  }
  if ((*(int *)(DAT_0112ebb4 + 0x16c) != 0) && (iVar2 != 0)) {
    iVar2 = *(int *)(iVar2 + 0x1ef8); // current crime ID
    FUN_004bab20(&local_10,*(int *)(DAT_0112ebb4 + 0x16c),iVar2); // get iterator for crimes
    while ((local_c != 0 || (local_8 != 0))) {
      iVar3 = (*(code *)*local_10)(); // get next crime
      if ((*(int *)(iVar3 + 8) == iVar1) && // crime type matches
         ((*(int *)(iVar3 + 0x10) == iVar2 && (0 < *(int *)(iVar3 + 0xc))))) { // crime ID matches and active
        iVar4 = iVar4 + 1;
      }
      (*(code *)local_10[2])(); // advance iterator
    }
  }
  return iVar4;
}