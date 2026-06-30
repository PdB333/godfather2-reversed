// FUNC_NAME: aes_ecb_encrypt
// Decrypts a 16-byte block using AES (Rijndael) with ECB mode.
// Uses T-table implementation from libtomcrypt.
// skey: pointer to symmetric_key struct containing expanded key schedule.
//   +0x100: start of encrption round keys (eK[60], uint32_t[60]? but used as rounds after initial)
//   +0x200: int Nr (number of rounds, values 10,12,14)
void aes_ecb_encrypt(const unsigned char *pt, unsigned char *ct, const symmetric_key *skey)
{
    uint32_t s0, s1, s2, s3, t0, t1, t2, t3;
    uint32_t rk[60]; // local copy of round keys? Actually we index directly into skey memory.
    const uint32_t *rk_start = (const uint32_t*)((const char*)skey + 0x100); // eK array
    int Nr = *(int*)((const char*)skey + 0x200); // key length in rounds (10/12/14)
    int rounds = (Nr - 1); // number of full rounds (excluding final)
    const uint32_t *Te0 = (const uint32_t*)0x00e28ee0; // Te0 = MixColumns+Forward transform
    const uint32_t *Te1 = (const uint32_t*)0x00e292e0;
    const uint32_t *Te2 = (const uint32_t*)0x00e296e0;
    const uint32_t *Te3 = (const uint32_t*)0x00e29ae0;
    const uint32_t *Te4 = (const uint32_t*)0x00e29ee0; // Te4 for final round (SubBytes+ShiftRows only)

    if (pt == 0) {
        fprintf(stderr, "_ARGCHK 'pt != NULL' failure on line 0x175 of file aes.c\n");
        return;
    }
    if (ct == 0) {
        fprintf(stderr, "_ARGCHK 'ct != NULL' failure on line 0x176 of file aes.c\n");
        return;
    }
    if (skey == 0) {
        fprintf(stderr, "_ARGCHK 'skey != NULL' failure on line 0x177 of file aes.c\n");
        return;
    }

    // Read plaintext as big-endian 32-bit words
    s0 = ((uint32_t)pt[0] << 24) | (pt[1] << 16) | (pt[2] << 8) | pt[3];
    s1 = ((uint32_t)pt[4] << 24) | (pt[5] << 16) | (pt[6] << 8) | pt[7];
    s2 = ((uint32_t)pt[8] << 24) | (pt[9] << 16) | (pt[10] << 8) | pt[11];
    s3 = ((uint32_t)pt[12] << 24) | (pt[13] << 16) | (pt[14] << 8) | pt[15];

    // Initial round: XOR with first round key (round 0)
    s0 ^= rk_start[0];
    s1 ^= rk_start[1];
    s2 ^= rk_start[2];
    s3 ^= rk_start[3];

    // Perform (Nr-1) full rounds: SubBytes, ShiftRows, MixColumns, AddRoundKey
    for (int r = 1; r <= rounds; r++) {
        t0 = Te0[(s0 >> 24) & 0xFF] ^ Te1[(s1 >> 16) & 0xFF] ^ Te2[(s2 >> 8) & 0xFF] ^ Te3[s3 & 0xFF] ^ rk_start[4*r];
        t1 = Te0[(s1 >> 24) & 0xFF] ^ Te1[(s2 >> 16) & 0xFF] ^ Te2[(s3 >> 8) & 0xFF] ^ Te3[s0 & 0xFF] ^ rk_start[4*r+1];
        t2 = Te0[(s2 >> 24) & 0xFF] ^ Te1[(s3 >> 16) & 0xFF] ^ Te2[(s0 >> 8) & 0xFF] ^ Te3[s1 & 0xFF] ^ rk_start[4*r+2];
        t3 = Te0[(s3 >> 24) & 0xFF] ^ Te1[(s0 >> 16) & 0xFF] ^ Te2[(s1 >> 8) & 0xFF] ^ Te3[s2 & 0xFF] ^ rk_start[4*r+3];
        s0 = t0; s1 = t1; s2 = t2; s3 = t3;
    }

    // Final round (no MixColumns)
    rk_start += 4*rounds; // advance pointer to round key after last full round
    t0 = (Te4[(s0 >> 24) & 0xFF] & 0xFF000000) ^ (Te4[(s1 >> 16) & 0xFF] & 0x00FF0000) ^ (Te4[(s2 >> 8) & 0xFF] & 0x0000FF00) ^ (Te4[s3 & 0xFF] & 0x000000FF) ^ rk_start[0];
    t1 = (Te4[(s1 >> 24) & 0xFF] & 0xFF000000) ^ (Te4[(s2 >> 16) & 0xFF] & 0x00FF0000) ^ (Te4[(s3 >> 8) & 0xFF] & 0x0000FF00) ^ (Te4[s0 & 0xFF] & 0x000000FF) ^ rk_start[1];
    t2 = (Te4[(s2 >> 24) & 0xFF] & 0xFF000000) ^ (Te4[(s3 >> 16) & 0xFF] & 0x00FF0000) ^ (Te4[(s0 >> 8) & 0xFF] & 0x0000FF00) ^ (Te4[s1 & 0xFF] & 0x000000FF) ^ rk_start[2];
    t3 = (Te4[(s3 >> 24) & 0xFF] & 0xFF000000) ^ (Te4[(s0 >> 16) & 0xFF] & 0x00FF0000) ^ (Te4[(s1 >> 8) & 0xFF] & 0x0000FF00) ^ (Te4[s2 & 0xFF] & 0x000000FF) ^ rk_start[3];

    // Write ciphertext in big-endian byte order
    ct[0] = (unsigned char)(t0 >> 24);
    ct[1] = (unsigned char)(t0 >> 16);
    ct[2] = (unsigned char)(t0 >> 8);
    ct[3] = (unsigned char)(t0);
    ct[4] = (unsigned char)(t1 >> 24);
    ct[5] = (unsigned char)(t1 >> 16);
    ct[6] = (unsigned char)(t1 >> 8);
    ct[7] = (unsigned char)(t1);
    ct[8] = (unsigned char)(t2 >> 24);
    ct[9] = (unsigned char)(t2 >> 16);
    ct[10] = (unsigned char)(t2 >> 8);
    ct[11] = (unsigned char)(t2);
    ct[12] = (unsigned char)(t3 >> 24);
    ct[13] = (unsigned char)(t3 >> 16);
    ct[14] = (unsigned char)(t3 >> 8);
    ct[15] = (unsigned char)(t3);
}