// FUNC_NAME: cryptPrimeGenerate
// Address: 0x0066cb20
// Role: Generates a random prime number using libtomcrypt's prime.c (likely rand_prime or mp_prime_random_ex).
// Parameters: param_1 = pointer to mp_int (prime), param_2 = bits / prng state? 
// Uses EAX register as "mode" and ESI as "prngIndex" (likely from caller or global).

// Forward declarations for external functions
extern int FUN_0066bad0(int condition, int* output);
extern int FUN_00669c80(void* prime, int value);
extern int FUN_0066cf40(void);
extern int _fprintf(FILE* stream, const char* format, ...);
extern int FUN_00b995f7(const char* format, ...); // likely string formatting for assert

// Global data: array of prng descriptors (5 bytes each? or pointers)
extern int DAT_01206408; // Base of table

int cryptPrimeGenerate(void* prime, int param_2) {
    int mode;           // from in_EAX register
    int prngIndex;      // from ESI register
    int temp;           // local_8
    int result;
    const char* errorFormat;

    // Assertion check: prime pointer must not be NULL
    if (prime == 0) {
        errorFormat = "_ARGCHK '%s' failure on line %d of file %s\n";
        result = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s",
                             "N != NULL", 0x23, "..\\src\\libtomcrypt\\prime.c");
        _fprintf((FILE*)(result + 0x40), errorFormat);
    }

    // Check mode: must be between 2 and 0x101 (inclusive? actually mode-2 < 0xFF)
    if ((mode - 2U) < 0xFF) {
        // Verify prng index and descriptor availability
        if ((prngIndex < 0x20) && (*(int*)((int)&DAT_01206408 + prngIndex * 5) != 0)) {
            // Call function to read random bytes from prng
            temp = param_2; // store param_2 (possibly flags or size)
            result = FUN_0066bad0(mode < 0, &temp); // pass condition and pointer to temp
            // Call prime generation routine
            int success = FUN_00669c80(prime, result);
            if (success != 0) {
                // Return error code from last function
                return FUN_0066cf40();
            }
            return 0; // success
        }
        return 0xc; // error: invalid prng or index
    }
    return 0x17; // error: invalid mode
}