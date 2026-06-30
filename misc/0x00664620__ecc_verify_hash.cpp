// FUNC_NAME: ecc_verify_hash
// Address: 0x00664620
// Source: c:\packages001_pc\tnl\dev\src\libtomcrypt\ecc_sys.c
// Purpose: Verify an ECDSA signature using the given key and hash.

int ecc_verify_hash(const unsigned char *sig, uint sigLen, const unsigned char *hash, int *stat, const ecc_key *key)
{
    uint uVar2;
    int iVar3, iVar4;
    char *errorStr;
    int local_78[4];              // mp_int arrays / workspaces
    unsigned char local_68[16];   // mp_int buffer
    unsigned char local_58[16];
    unsigned char local_48[16];
    unsigned char local_38[8];    // mp_int buffer
    unsigned char local_30[48];   // temporary mp_int

    // Parameter validation
    if (sig == NULL) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar3 = FUN_00b995f7(errorStr, "sig != NULL", 0x140,
                             "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf((FILE *)(iVar3 + 0x40), errorStr);
    }
    if (hash == NULL) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar3 = FUN_00b995f7(errorStr, "hash != NULL", 0x141,
                             "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf((FILE *)(iVar3 + 0x40), errorStr);
    }
    if (stat == NULL) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar3 = FUN_00b995f7(errorStr, "stat != NULL", 0x142,
                             "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf((FILE *)(iVar3 + 0x40), errorStr);
    }
    if (key == NULL) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar3 = FUN_00b995f7(errorStr, "key != NULL", 0x143,
                             "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf((FILE *)(iVar3 + 0x40), errorStr);
    }

    *stat = 0;

    // Minimum signature size check (header + data)
    if (sigLen < 12) {
        return 7;  // CRYPT_INVALID_PACKET?
    }

    // Initialize multiple precision integers (calls mp_init_multi)
    iVar3 = FUN_0066c9f0(2);
    if (iVar3 != 0) {
        return iVar3;
    }

    // Read the "hash size" from signature header at offset 4
    uVar2 = *(uint *)(sig + 4);
    if (sigLen - 12 < uVar2) {
        return 7;
    }

    // Decode the dot-product or scalar from signature data
    iVar3 = FUN_00663a00(sig + 8, uVar2, local_38);  // decode raw bytes to mp_int local_38
    if (iVar3 != 0) {
        return iVar3;
    }

    // Pointer to next component after first scalar
    uint *puVar1 = (uint *)(uVar2 + 8 + sig);
    if ((sigLen - 12) - uVar2 < *puVar1) {
        return 7;
    }

    // Initialize mp_ints for the verification process
    iVar3 = FUN_00667820(local_58, local_48, local_78, local_68, 0); // mp_init_multi?
    if (iVar3 != 0) {
        goto error_cleanup;
    }

    // Check if the key is suitable (public key present?)
    iVar3 = FUN_00662440(); // ecc_is_valid_idx or similar
    if (iVar3 == 0) {
        FUN_00665b80(local_58, local_48, local_78, local_68, 0); // mp_clear_multi
        goto error_cleanup;
    }

    // Check that the signature components are non-zero (prevent small subgroup attacks)
    iVar4 = FUN_0066a010(puVar1 + 1); // mp_iszero on R?
    if ((iVar4 == 0) && (iVar4 = FUN_0066a010(hash), iVar4 == 0)) {
        // Load the curve parameters (domain string based on key type)
        iVar4 = FUN_00669f00((&PTR_s_G00000000000000000000000007_00e279c8)[*(int *)(key + 4) * 7],
                             0x40); // mp_read_radix using a curve OID string
        if (iVar4 == 0) {
            // Perform ECC signature verification steps
            FUN_0066a550(); // probably a hash-related operation
            FUN_006687e0(local_78[0] * 2); // some modular multiplication preparation
            iVar4 = FUN_00665d70(local_68, local_78, local_68, 0); // mp_invmod or similar
            if (iVar4 != 0) {
                iVar3 = 0xd; // CRYPT_INVALID_PACKET?
                goto exit_cleanup;
            }

            // Compute modular inverse of the hash (e)
            iVar4 = FUN_00662a30(local_58, local_30, local_30, local_78); // mp_mulmod?
            if ((((iVar4 == 0) &&
                  (iVar4 = FUN_006626f0(local_30, key + 8, local_30, local_78, local_68), iVar4 == 0)) &&
                 (iVar4 = FUN_00669f00((&PTR_s_jpqOf1BHus6Yd_pyhyVpP_00e279d4)[*(int *)(key + 4) * 7],
                                       0x40), iVar4 == 0)) &&
                ((iVar4 = FUN_00669f00((&PTR_s_D_wykuuIFfr_vPyx7kQEPu8MixO_00e279d8)
                                       [*(int *)(key + 4) * 7], 0x40), iVar4 == 0 &&
                 (iVar3 = FUN_00662a30(local_48, iVar3, iVar3, local_78), iVar3 == 0)))) {
                // Verify the final point and set stat accordingly
                iVar3 = FUN_00665bd0(); // check if r == computed x coordinate?
                if ((iVar3 == 0) && (iVar3 = FUN_00665bd0(), iVar3 == 0)) {
                    *stat = 1; // signature valid
                }
                iVar3 = 0;
                goto exit_cleanup;
            }
        }
    }

    iVar3 = 1; // generic error (CRYPT_ERROR?)

exit_cleanup:
    FUN_00662480(); // free allocated memory?
    FUN_00663460(); // mp_clear?
    FUN_00665b80(local_78, local_48, local_58, local_68, 0); // mp_clear_multi
    return iVar3;

error_cleanup:
    FUN_00663460();
    return 0xd; // CRYPT_MEMORY?
}