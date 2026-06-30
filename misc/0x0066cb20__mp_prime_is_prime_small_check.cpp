// FUNC_NAME: mp_prime_is_prime_small_check
int mp_prime_is_prime_small_check(int N, int *result) {
    // Assert: N must be non-NULL (from libtomcrypt prime.c line 0x23)
    if (N == 0) {
        const char *format = "_ARGCHK '%s' failure on line %d of file %s\n";
        int argInfo = mp_arg_check("_ARGCHK '%s' failure on line %d of file %s", 
                                   "N != NULL", 0x23, 
                                   "..\\src\\libtomcrypt\\prime.c");
        __fprintf((FILE *)(argInfo + 0x40), format);
    }

    int candidate = in_EAX; // The integer value being tested (passed in EAX)
    int idx = unaff_ESI;   // Current index into small prime table (passed in ESI)

    // If candidate is a small prime (2 <= candidate <= 256)
    if ((unsigned int)(candidate - 2) < 0xff) {
        // idx must be in range and the prime table entry non-zero
        if (idx < 0x20 && prime_table[idx * 5] != 0) {
            int localResult = *result; // original result value (may be modified by mp_cmp_d)
            int cmpResult = mp_cmp_d(candidate < 0, &localResult); // compare candidate with digit from table?
            int modResult = mp_mod_d(N, cmpResult);
            if (modResult != 0) {
                return mp_prime_is_prime_error();
            }
            return 0; // Success: number passed quick test
        }
        return 0xc; // Error: composite (not prime)
    }
    return 0x17; // Error: number too large for this quick test
}