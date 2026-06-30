// FUNC_NAME: aes_decrypt
// Function address: 0x00661210
// Role: AES decryption (from LibTomCrypt, aes.c)
// Decrypts a 16-byte block using the AES key schedule.
// Parameters:
//   inputBlock: 16-byte ciphertext block
//   outputBlock: 16-byte plaintext block (output)
//   skey: pointer to AES key schedule (symmetric_key struct)
// The key schedule structure is assumed to contain:
//   - skey[0..3] : initial round key
//   - skey[4..7] : next round key
//   - ... (each round key is 4 words)
//   - skey[0x80] : value that when shifted right by 1 gives the number of loop iterations
//                  (each iteration processes 2 rounds, total rounds = 1 + 2*iterations + 1)
// The global tables Te0, Te1, Te2, Te3 (encryption tables) are used for the main rounds.
// The final round uses the inverse substitution table Td0 (DAT_00e28ae0).

void aes_decrypt(unsigned char *inputBlock, unsigned char *outputBlock, unsigned int *skey)
{
    unsigned int s0, s1, s2, s3;  // state words
    unsigned int t0, t1, t2, t3;  // temporary words during rounds
    int roundCount;               // number of loop iterations (each process 2 rounds)
    char *errorMsg;

    // Null pointer checks with _ARGCHK macro
    if (inputBlock == (unsigned char *)0x0) {
        errorMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        roundCount = FUN_00b995f7("pt != NULL", 0xf6, "..\\src\\libtomcrypt\\aes.c");
        _fprintf((FILE *)(roundCount + 0x40), errorMsg);
    }
    if (outputBlock == (unsigned char *)0x0) {
        errorMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        roundCount = FUN_00b995f7("ct != NULL", 0xf7, "..\\src\\libtomcrypt\\aes.c");
        _fprintf((FILE *)(roundCount + 0x40), errorMsg);
    }
    if (skey == (unsigned int *)0x0) {
        errorMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        roundCount = FUN_00b995f7("skey != NULL", 0xf8, "..\\src\\libtomcrypt\\aes.c");
        _fprintf((FILE *)(roundCount + 0x40), errorMsg);
    }

    // Load input block into state (big-endian words from bytes)
    // s0 = bytes[0..3] big-endian, etc.
    s0 = (inputBlock[0] << 24) | (inputBlock[1] << 16) | (inputBlock[2] << 8) | inputBlock[3];
    s1 = (inputBlock[4] << 24) | (inputBlock[5] << 16) | (inputBlock[6] << 8) | inputBlock[7];
    s2 = (inputBlock[8] << 24) | (inputBlock[9] << 16) | (inputBlock[10] << 8) | inputBlock[11];
    s3 = (inputBlock[12] << 24) | (inputBlock[13] << 16) | (inputBlock[14] << 8) | inputBlock[15];

    // Initial AddRoundKey (round key 0)
    s0 ^= skey[0];
    s1 ^= skey[1];
    s2 ^= skey[2];
    s3 ^= skey[3];

    // First round (round 1) using Te tables
    t0 = Te0[(s0 >> 24)] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ skey[4];
    t1 = Te0[(s1 >> 24)] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ skey[5];
    t2 = Te0[(s2 >> 24)] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ skey[6];
    t3 = Te0[(s3 >> 24)] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ skey[7];

    // Update state for next round
    s0 = t0;
    s1 = t1;
    s2 = t2;
    s3 = t3;

    // Main rounds: process 2 rounds per iteration
    // Total iterations = (skey[0x80] >> 1) - 1? Actually loop runs while roundCount--
    // roundCount initialized from skey[0x80] >> 1
    roundCount = (int)(skey[0x80] >> 1); // number of loop iterations (each iteration does 2 rounds)
    // The loop decrements roundCount and runs while != 0
    // First iteration already done, so loop count = roundCount - 1 (but the initial for loop above is actually part of the first iteration)
    // In this reconstruction, we adjust: the loop below will run for the remaining iterations.
    // The original code structure: first round done outside, then loop with iVar--.
    // Here iVar = skey[0x80] >> 1. The loop runs (iVar) times? Actually while(iVar != 0) with post-decrement.
    // To match the original, we need to start roundCount as (skey[0x80] >> 1) and then loop while (--roundCount != 0)
    // But the original code: iVar = skey[0x80] >> 1; ... while (iVar = iVar + -1, iVar != 0)
    // That means iVar is decremented and then checked. So if initial iVar = N, the loop body runs N-1 times.
    // We'll implement accordingly.
    roundCount = (skey[0x80] >> 1) - 1; // number of additional iterations
    while (roundCount-- > 0)
    {
        // Round pair (2 rounds) using alternating round keys
        // First round of the pair uses skey[+2, +1, +0, +3] (order as per original)
        t0 = Te0[(s0 >> 24)] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ skey[2];
        t1 = Te0[(s1 >> 24)] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ skey[1];
        t2 = Te0[(s2 >> 24)] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ skey[0];
        t3 = Te0[(s3 >> 24)] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ skey[3];

        // Second round of the pair with +4 offset
        s0 = Te0[(t0 >> 24)] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ skey[4];
        s1 = Te0[(t1 >> 24)] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ skey[5];
        s2 = Te0[(t2 >> 24)] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ skey[6];
        s3 = Te0[(t3 >> 24)] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ skey[7];

        // Advance key schedule pointer by 8 words for next round pair
        skey += 8;
    }

    // Final round: use inverse substitution table Td0
    // No MixColumns; only SubBytes, ShiftRows, AddRoundKey
    unsigned int final0, final1, final2, final3;
    final0 = Td0[(s0 >> 24)] & 0xff000000 ^ Td0[(s1 >> 16) & 0xff] & 0x00ff0000 ^
             Td0[(s2 >> 8) & 0xff] & 0x0000ff00 ^ Td0[s3 & 0xff] & 0x000000ff ^ skey[0];
    final1 = Td0[(s1 >> 24)] & 0xff000000 ^ Td0[(s2 >> 16) & 0xff] & 0x00ff0000 ^
             Td0[(s3 >> 8) & 0xff] & 0x0000ff00 ^ Td0[s0 & 0xff] & 0x000000ff ^ skey[1];
    final2 = Td0[(s2 >> 24)] & 0xff000000 ^ Td0[(s3 >> 16) & 0xff] & 0x00ff0000 ^
             Td0[(s0 >> 8) & 0xff] & 0x0000ff00 ^ Td0[s1 & 0xff] & 0x000000ff ^ skey[2];
    final3 = Td0[(s3 >> 24)] & 0xff000000 ^ Td0[(s0 >> 16) & 0xff] & 0x00ff0000 ^
             Td0[(s1 >> 8) & 0xff] & 0x0000ff00 ^ Td0[s2 & 0xff] & 0x000000ff ^ skey[3];

    // Store result in output block (byte-by-byte, big-endian)
    outputBlock[0] = (unsigned char)(final0 >> 24);
    outputBlock[1] = (unsigned char)(final0 >> 16);
    outputBlock[2] = (unsigned char)(final0 >> 8);
    outputBlock[3] = (unsigned char)(final0);
    outputBlock[4] = (unsigned char)(final1 >> 24);
    outputBlock[5] = (unsigned char)(final1 >> 16);
    outputBlock[6] = (unsigned char)(final1 >> 8);
    outputBlock[7] = (unsigned char)(final1);
    outputBlock[8] = (unsigned char)(final2 >> 24);
    outputBlock[9] = (unsigned char)(final2 >> 16);
    outputBlock[10] = (unsigned char)(final2 >> 8);
    outputBlock[11] = (unsigned char)(final2);
    outputBlock[12] = (unsigned char)(final3 >> 24);
    outputBlock[13] = (unsigned char)(final3 >> 16);
    outputBlock[14] = (unsigned char)(final3 >> 8);
    outputBlock[15] = (unsigned char)(final3);
}