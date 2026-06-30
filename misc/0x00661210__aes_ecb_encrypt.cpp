// FUNC_NAME: aes_ecb_encrypt
void aes_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey)
{
    uint s0, s1, s2, s3;
    uint t0, t1, t2, t3;
    uint r;
    int i;

    // Parameter validation (ARGCHK)
    if (pt == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "pt != NULL", 0xf6, "../src/libtomcrypt/aes.c");
        return;
    }
    if (ct == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "ct != NULL", 0xf7, "../src/libtomcrypt/aes.c");
        return;
    }
    if (skey == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "skey != NULL", 0xf8, "../src/libtomcrypt/aes.c");
        return;
    }

    // Load plaintext into state (big-endian)
    s0 = (uint32_t)(pt[0] << 24 | pt[1] << 16 | pt[2] << 8 | pt[3]) ^ skey->eK[0];
    s1 = (uint32_t)(pt[4] << 24 | pt[5] << 16 | pt[6] << 8 | pt[7]) ^ skey->eK[1];
    s2 = (uint32_t)(pt[8] << 24 | pt[9] << 16 | pt[10] << 8 | pt[11]) ^ skey->eK[2];
    s3 = (uint32_t)(pt[12] << 24 | pt[13] << 16 | pt[14] << 8 | pt[15]) ^ skey->eK[3];

    // First round (already xored with round key 0)
    // Note: The original code does AddRoundKey inside the table lookups? Actually it initializes after loading state then does a partial round? Let's check decompiled:
    // It does: uVar4 = T0[s3>>8..] ^ T1[s2>>16..] ^ T2[s1>>24] ^ T3[s0&0xff] ^ skey[4]; That's the first round output.
    // So we need to apply SubBytes, ShiftRows, MixColumns, AddRoundKey (round key 1). The decompiled code starts with a round after the initial xor, then loop for Nr-1 rounds, then final round.
    // We'll replicate the logic exactly.

    // Number of rounds (Nr = skey->Nr)
    r = skey->Nr; // Typically 10 for AES-128, 12 for AES-192, 14 for AES-256
    i = (r >> 1); // Because we process two rounds per iteration? Actually the loop decrements i and uses param_3 += 8 each iteration (processing 2 round keys per loop). So the number of loop iterations is r/2.
    // The code: iVar1 = (int)param_3[0x80] >> 1; Then while (iVar1 += -1, iVar1 != 0). So it runs r/2 -1? Actually it initializes iVar1 = param_3[0x80] >> 1 then decrements and loops while not zero. So it runs that many times. For AES-128, r=10, r/2=5, but the loop includes one initial round done before the loop? Let's trace:
    // Before loop: after initial XOR, we compute t0,t1,t2,t3 (first round output) and then loop for i = (Nr/2)-1? Actually we need to examine the code more carefully.
    // The decompiled code: 
    // uVar4 = ... ^ param_3[4]; (first round output)
    // uVar6 = ... ^ param_3[5];
    // uVar8 = ... ^ param_3[6];
    // uVar2 = ... ^ param_3[7];
    // Then param_3 = param_3 + 8; and while (--i != 0) { ... }
    // So the first two rounds (rounds 1 and 2) are done before the loop? Actually after initial XOR (round0), we compute the first round output (s0..s3 become t0..t3?) and we XOR with round keys 4-7 (that's round 1?). Wait, the initial XOR uses skey[0..3]. Then we compute new state using s0..s3 and XOR with skey[4..7]. That's round 1. Then we loop processing two rounds per iteration (since each loop iteration uses 8 keys). So the loop processes rounds 2 to Nr-1? Then after loop, a final round using T4 table.
    // Standard AES encryption: for each round except last: SubBytes, ShiftRows, MixColumns, AddRoundKey. Final round: SubBytes, ShiftRows, AddRoundKey. Here the linear loop does MixColumns for every round except the last. So the loop must handle rounds 1 to Nr-1. The number of loop iterations is (Nr-2)/2? Let's derive from the code:
    // i = Nr >> 1; initially. Then after the first round (which uses keys 4-7), we do while (--i != 0) { ... } meaning we process (Nr/2 - 1) iterations. Each iteration does two rounds (since it uses 8 keys). So total rounds done in loop = 2 * (Nr/2 - 1) = Nr - 2. Plus the first round (keys 4-7) = Nr - 1 rounds. Then final round (keys after loop). That matches: first round (round 1), then loop for rounds 2 to Nr-1, then final round (round Nr). So the loop deals with rounds 2..Nr-1. For AES-128, Nr=10, so loop runs (10/2 -1)=4 iterations, each does 2 rounds => rounds 2-9 (8 rounds) + first round = 9 rounds, then final round (round 10). Good.
    // So we'll implement accordingly.

    // Perform first round (round 1) - compute state after first full round
    t0 = T0[(uint8_t)(s0 >> 24)] ^ 
         T1[(uint8_t)(s1 >> 16)] ^ 
         T2[(uint8_t)(s2 >> 8)] ^ 
         T3[(uint8_t)s3] ^ skey->eK[4];
    t1 = T0[(uint8_t)(s1 >> 24)] ^ 
         T1[(uint8_t)(s2 >> 16)] ^ 
         T2[(uint8_t)(s3 >> 8)] ^ 
         T3[(uint8_t)s0] ^ skey->eK[5];
    t2 = T0[(uint8_t)(s2 >> 24)] ^ 
         T1[(uint8_t)(s3 >> 16)] ^ 
         T2[(uint8_t)(s0 >> 8)] ^ 
         T3[(uint8_t)s1] ^ skey->eK[6];
    t3 = T0[(uint8_t)(s3 >> 24)] ^ 
         T1[(uint8_t)(s0 >> 16)] ^ 
         T2[(uint8_t)(s1 >> 8)] ^ 
         T3[(uint8_t)s2] ^ skey->eK[7];

    s0 = t0; s1 = t1; s2 = t2; s3 = t3;

    // Advance round key pointer (we already used 4-7, next are 8-...)
    // In the code, param_3 was incremented by 8 before loop. So we'll use skey->eK + 8 as starting point for loop.
    uint *rk = skey->eK + 8;
    i = (skey->Nr >> 1) - 1; // Number of loop iterations (each iteration does two rounds)

    while (i--) {
        // Round (even) - using current s values
        t0 = T0[(uint8_t)(s0 >> 24)] ^ 
             T1[(uint8_t)(s1 >> 16)] ^ 
             T2[(uint8_t)(s2 >> 8)] ^ 
             T3[(uint8_t)s3] ^ rk[2];
        t1 = T0[(uint8_t)(s1 >> 24)] ^ 
             T1[(uint8_t)(s2 >> 16)] ^ 
             T2[(uint8_t)(s3 >> 8)] ^ 
             T3[(uint8_t)s0] ^ rk[1]; // note order: in decompiled, t1 uses rk[1]? Actually need to match precisely. Let's check decompiled for the loop: 
             // It computes:
             // uVar7 = ... ^ param_3[2];   // t0? Actually uVar7 is first computed then used later. But careful: In the loop, the order of assignments is:
             // uVar7 = ... ^ param_3[2];   // this becomes the new s0 after round? Actually the decompiled variable naming is messy. Let's re-extract the loop from decompiled:
             // uVar7 = ... ^ param_3[2];
             // uVar5 = ... ^ param_3[1];
             // uVar3 = ... ^ *param_3;
             // uVar2 = ... ^ param_3[3];
             // uVar4 = ... ^ param_3[4];
             // uVar6 = ... ^ param_3[5];
             // uVar8 = ... ^ param_3[6];
             // uVar2 = ... ^ param_3[7];
             // So the first four are for one round, the next four for the next round within the same iteration? Actually this loop processes 8 keys (two rounds) per iteration. The computed values uVar7, uVar5, uVar3, uVar2 are for the first round (odd round) and then uVar4, uVar6, uVar8, uVar2 (overwrites uVar2) are for the second round (even round). Then at the end of the loop, s0..s3 are updated from the second round. So we need to replicate that exactly. Since we are reconstructing, we can simplify by doing two rounds per iteration explicitly using temp variables.

        // We'll implement two rounds per iteration as per original:
        // First round of this iteration (odd round number)
        uint new_s0, new_s1, new_s2, new_s3;
        new_s0 = T0[(uint8_t)(s0 >> 24)] ^ 
                 T1[(uint8_t)(s1 >> 16)] ^ 
                 T2[(uint8_t)(s2 >> 8)] ^ 
                 T3[(uint8_t)s3] ^ rk[2];
        new_s1 = T0[(uint8_t)(s1 >> 24)] ^ 
                 T1[(uint8_t)(s2 >> 16)] ^ 
                 T2[(uint8_t)(s3 >> 8)] ^ 
                 T3[(uint8_t)s0] ^ rk[1];
        new_s2 = T0[(uint8_t)(s2 >> 24)] ^ 
                 T1[(uint8_t)(s3 >> 16)] ^ 
                 T2[(uint8_t)(s0 >> 8)] ^ 
                 T3[(uint8_t)s1] ^ rk[0];
        new_s3 = T0[(uint8_t)(s3 >> 24)] ^ 
                 T1[(uint8_t)(s0 >> 16)] ^ 
                 T2[(uint8_t)(s1 >> 8)] ^ 
                 T3[(uint8_t)s2] ^ rk[3];
        // Second round of this iteration (even round number)
        s0 = T0[(uint8_t)(new_s0 >> 24)] ^ 
             T1[(uint8_t)(new_s1 >> 16)] ^ 
             T2[(uint8_t)(new_s2 >> 8)] ^ 
             T3[(uint8_t)new_s3] ^ rk[4];
        s1 = T0[(uint8_t)(new_s1 >> 24)] ^ 
             T1[(uint8_t)(new_s2 >> 16)] ^ 
             T2[(uint8_t)(new_s3 >> 8)] ^ 
             T3[(uint8_t)new_s0] ^ rk[5];
        s2 = T0[(uint8_t)(new_s2 >> 24)] ^ 
             T1[(uint8_t)(new_s3 >> 16)] ^ 
             T2[(uint8_t)(new_s0 >> 8)] ^ 
             T3[(uint8_t)new_s1] ^ rk[6];
        s3 = T0[(uint8_t)(new_s3 >> 24)] ^ 
             T1[(uint8_t)(new_s0 >> 16)] ^ 
             T2[(uint8_t)(new_s1 >> 8)] ^ 
             T3[(uint8_t)new_s2] ^ rk[7];
        rk += 8;
    }

    // Final round (no MixColumns)
    // Use T4 table for SubBytes and ShiftRows only, then add round key.
    // The code uses T4 (DAT_00e28ae0) and extracts bytes with masks.
    // Let's replicate:
    t0 = (T4[(uint8_t)(s0 >> 24)] & 0xFF000000) ^
         (T4[(uint8_t)(s1 >> 16)] & 0x00FF0000) ^
         (T4[(uint8_t)(s2 >> 8)]  & 0x0000FF00) ^
         (T4[(uint8_t)s3]        & 0x000000FF) ^ rk[0];
    t1 = (T4[(uint8_t)(s1 >> 24)] & 0xFF000000) ^
         (T4[(uint8_t)(s2 >> 16)] & 0x00FF0000) ^
         (T4[(uint8_t)(s3 >> 8)]  & 0x0000FF00) ^
         (T4[(uint8_t)s0]        & 0x000000FF) ^ rk[1];
    t2 = (T4[(uint8_t)(s2 >> 24)] & 0xFF000000) ^
         (T4[(uint8_t)(s3 >> 16)] & 0x00FF0000) ^
         (T4[(uint8_t)(s0 >> 8)]  & 0x0000FF00) ^
         (T4[(uint8_t)s1]        & 0x000000FF) ^ rk[2];
    t3 = (T4[(uint8_t)(s3 >> 24)] & 0xFF000000) ^
         (T4[(uint8_t)(s0 >> 16)] & 0x00FF0000) ^
         (T4[(uint8_t)(s1 >> 8)]  & 0x0000FF00) ^
         (T4[(uint8_t)s2]        & 0x000000FF) ^ rk[3];

    // Store ciphertext in big-endian
    ct[0] = (t0 >> 24) & 0xFF;
    ct[1] = (t0 >> 16) & 0xFF;
    ct[2] = (t0 >> 8) & 0xFF;
    ct[3] = t0 & 0xFF;
    ct[4] = (t1 >> 24) & 0xFF;
    ct[5] = (t1 >> 16) & 0xFF;
    ct[6] = (t1 >> 8) & 0xFF;
    ct[7] = t1 & 0xFF;
    ct[8] = (t2 >> 24) & 0xFF;
    ct[9] = (t2 >> 16) & 0xFF;
    ct[10] = (t2 >> 8) & 0xFF;
    ct[11] = t2 & 0xFF;
    ct[12] = (t3 >> 24) & 0xFF;
    ct[13] = (t3 >> 16) & 0xFF;
    ct[14] = (t3 >> 8) & 0xFF;
    ct[15] = t3 & 0xFF;
}