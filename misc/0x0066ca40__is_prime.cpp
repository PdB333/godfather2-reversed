// FUNC_NAME: is_prime
int __cdecl is_prime(mp_int *N, int *result)
{
    int iVar1;
    uint uVar2;
    int iVar3;
    mp_int *N_orig; // from ESI
    int *result_orig; // from EDI
    char *errorMsg;

    // Parameter validation
    if (N == NULL) {
        iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n", "N != NULL", 0x11, "..\\src\\libtomcrypt\\prime.c");
        _fprintf((FILE *)(iVar1 + 0x40), "%s", errorMsg);
    }
    if (result == NULL) {
        iVar1 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n", "result != NULL", 0x12, "..\\src\\libtomcrypt\\prime.c");
        _fprintf((FILE *)(iVar1 + 0x40), "%s", errorMsg);
    }

    // Check if N is non-zero, then count bits (loop shifting right until zero)
    if (*N != 0) {
        uVar2 = *(uint *)(N->dp[3] - 4 + *N * 4); // likely mp_digit size access
        while (uVar2 != 0) {
            uVar2 >>= 1;
        }
    }

    // Call mp_prime_is_prime or similar
    FUN_0066bad0();

    // Call mp_prime_random or similar
    iVar1 = FUN_00669570();
    if (iVar1 != 0) {
        // Check against a table of known small primes (3 entries)
        iVar3 = 0;
        do {
            if (iVar1 == (&DAT_00e2747c)[iVar3 * 2]) {
                return *(int *)(&UNK_00e27480 + iVar3 * 8);
            }
            iVar3 = iVar3 + 1;
        } while (iVar3 < 3);
        return 1; // prime found but not in table
    }
    return 0; // not prime
}