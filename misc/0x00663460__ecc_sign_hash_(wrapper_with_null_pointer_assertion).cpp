// FUNC_NAME: ecc_sign_hash (wrapper with null pointer assertion)
// Address: 0x00663460
// Role: This function appears to be a wrapper around an ECC signature computation from libtomcrypt.
// It checks if the key pointer is NULL, prints an assertion failure, then calls the internal
// signing function with offsets into the key structure (likely dp pointer, pubkey, k).

void eccSignHash(void* key) // key passed in EAX (likely __fastcall or __thiscall with ECX)
{
    if (key == 0) {
        // ARGCHK failure from libtomcrypt
        int iVar1 = FUN_00b995f7(
            "_ARGCHK '%s' failure on line %d of file %s\n",
            "key != NULL",
            0x291, // line 657 in ecc.c
            "..\\src\\libtomcrypt\\ecc.c"
        );
        _fprintf(
            (FILE*)(iVar1 + 0x40), // stderr or similar stream
            "_ARGCHK '%s' failure on line %d of file %s\n",
            "key != NULL",
            0x291,
            "..\\src\\libtomcrypt\\ecc.c"
        );
    }

    // Call the core ECC signing routine
    // Key structure offsets:
    //   +0x08: dp (ecc_set_type*)
    //   +0x18: pubkey.x (mp_int)
    //   +0x28: k (mp_int) or signhash
    FUN_00665b80(
        (uint8_t*)key + 0x08,
        (uint8_t*)key + 0x18,
        (uint8_t*)key + 0x28,
        0 // possibly PRNG or flags
    );
}