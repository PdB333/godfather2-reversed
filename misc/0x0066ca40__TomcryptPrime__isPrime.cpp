// FUNC_NAME: TomcryptPrime::isPrime
int TomcryptPrime::isPrime(void)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *N; // unaff_ESI
  int result; // unaff_EDI
  
  if (N == (int *)0x0) {
    // _ARGCHK 'N != NULL' failure on line 17 of file "..\\src\\libtomcrypt\\prime.c"
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","N != NULL",0x11,
                         "..\\src\\libtomcrypt\\prime.c");
    _fprintf((FILE *)(iVar1 + 0x40),"_ARGCHK '%s' failure on line %d of file %s\n");
  }
  if (result == 0) {
    // _ARGCHK 'result != NULL' failure on line 18 of file "..\\src\\libtomcrypt\\prime.c"
    iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","result != NULL",0x12,
                         "..\\src\\libtomcrypt\\prime.c");
    _fprintf((FILE *)(iVar1 + 0x40),"_ARGCHK '%s' failure on line %d of file %s\n");
  }
  if (*N != 0) {
    // Calculate bit length of N
    for (uVar2 = *(uint *)(N[3] + -4 + *N * 4); uVar2 != 0; uVar2 = uVar2 >> 1) {
    }
  }
  FUN_0066bad0(); // likely mp_init or similar
  iVar1 = FUN_00669570(); // likely mp_isprime or Montgomery setup
  if (iVar1 != 0) {
    iVar3 = 0;
    do {
      if (iVar1 == (&DAT_00e2747c)[iVar3 * 2]) {
        return *(undefined4 *)(&UNK_00e27480 + iVar3 * 8);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
    return 1;
  }
  return 0;
}