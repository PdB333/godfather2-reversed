// FUNC_NAME: ctr_start
// Address: 0x006649b0
// Role: Initialize CTR mode encryption (libtomcrypt)
// File: ..\src\libtomcrypt\ctr.c

#include <cstdio>
#include <cstdlib>

// Cipher descriptor table (0x2c bytes per entry)
// +0x00: uint (registered flag)
// +0x04: uint (block_size)
// +0x08: void* (setup function)
// +0x0c: void* (encrypt function)
// +0x10: ... (others)
#define CIPHER_DESC_SIZE 0x2c

extern uint registered_flag_table[32];  // DAT_01205a88
extern uint block_size_table[32];        // DAT_01205a98
extern void* cipher_setup_table[32];      // DAT_01205aa0
extern void* cipher_encrypt_table[32];    // DAT_01205aa4

// CTR state structure (symmetric_CTR)
struct symmetric_CTR {
    int cipher;        // +0x00: cipher index
    int blocklen;      // +0x04: block size
    int padlen;        // +0x08: padding length
    unsigned char IV[32];          // +0x0c: IV (max 32 bytes)
    unsigned char counter[32];     // +0x23? Actually offset 0x23 in original code? Wait: original uses in_EAX+3 and in_EAX+0x23 (35 decimal) and in_EAX+0x43 (67). So structure: +0x00 cipher, +0x04 blocklen, +0x08 padlen, +0x0c IV[blocklen], then counter at +0x0c+blocklen? Actually code: copies IV to in_EAX + iVar1 + 0xc for blocklen bytes. Then calls encrypt with in_EAX+3 (counter) and in_EAX+0x23 (encrypted counter) and in_EAX+0x43 (key schedule). So: +0x03 = counter? That would be misaligned. Let's re-evaluate: The struct likely has:
    //   int cipher;           // +0x00
    //   int blocklen;         // +0x04
    //   int padlen;           // +0x08
    //   unsigned char IV[32]; // +0x0c
    //   unsigned char counter[32]; // +0x2c? But code uses +3 for counter? Actually code: in_EAX + 3 is the address passed to encrypt as first argument (counter). And in_EAX + 0x23 (35) is second argument (encrypted counter). So counter is at +3 bytes? That would be odd alignment. Perhaps the struct has a different layout. But we'll keep the standard libtomcrypt layout: symmetric_CTR has:
    //   int cipher, blocklen, padlen;
    //   unsigned char IV[MAXBLOCKSIZE];
    //   unsigned char ctr[MAXBLOCKSIZE];
    //   unsigned char pad[MAXBLOCKSIZE];
    // and the key schedule is appended at end (symmetric_key?).
    // For simplicity, we just use raw offsets as in code.
    // In the code, the key schedule is at in_EAX + 0x43 (67). So the struct size is at least 67 + sizeof(symmetric_key).
    // We'll just use void* and offsets.
};

int ctr_start(int cipher, const unsigned char* IV, const unsigned char* key, int keylen, symmetric_CTR* ctr)
{
    // Parameter validation
    if (IV == 0) {
        int line = 10;
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "count != NULL", line, "..\\src\\libtomcrypt\\ctr.c");
        // In original code, it returns but continues? Actually it just prints and continues.
    }
    if (key == 0) {
        int line = 11;
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "key != NULL", line, "..\\src\\libtomcrypt\\ctr.c");
    }
    if (ctr == 0) {
        int line = 12;
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "ctr != NULL", line, "..\\src\\libtomcrypt\\ctr.c");
    }

    // Check cipher validity
    if (cipher < 32 && registered_flag_table[cipher] != 0) {
        // cipher descriptor setup function: (func) (key, keylen, 0, ctr->symmetric_key)
        int result = ((int (*)(const unsigned char*, int, int, void*))cipher_setup_table[cipher])(key, keylen, 0, (char*)ctr + 0x43);
        if (result == 0) {
            // Copy block length from cipher descriptor (at +0x04? Actually we have a separate table for block sizes)
            ctr->blocklen = block_size_table[cipher];   // from DAT_01205a98
            ctr->cipher = cipher;
            ctr->padlen = 0;   // initialize padding count

            // Copy IV into ctr->IV (at offset +0x0c)
            for (int i = 0; i < ctr->blocklen; i++) {
                *((unsigned char*)ctr + 0xc + i) = IV[i];
            }

            // Call cipher encrypt function on the counter (at +3? Actually in original code: in_EAX+3 is counter text, in_EAX+0x23 is output)
            // This initializes the encrypted counter buffer
            void* counter = (unsigned char*)ctr + 3;   // Actually standard offset is 0x0c+blocklen? But we follow original offset
            void* enc_counter = (unsigned char*)ctr + 0x23;
            void* key_schedule = (unsigned char*)ctr + 0x43;
            // Encrypt the initial counter
            // Note: original code does not seem to copy the counter? It assumes the IV is at a fixed offset? But standard CTR: IV is used as counter.
            // Actually in libtomcrypt ctr_start, it first copies IV to ctr->ctr (counter) and then encrypts it.
            // But here it encrypts from in_EAX+3, which is likely the counter field offset.
            // So we need to set the counter (IV) first. Since IV is already copied to ctr+0xc, but the counter starts at +3?
            // This suggests the struct layout is: 
            // +0x00: cipher (int)
            // +0x04: blocklen (int)
            // +0x08: padlen (int)
            // +0x0c: IV[?] up to blocklen
            // +0x0c+blocklen: counter[?]  (but then offset +3 is inside the IV? Inconsistent.)
            // Given the original code uses +3 as counter and +0x23 as enc_counter, and +0x43 for key schedule, it's likely a hand-optimized or custom layout.
            // For reverse engineering correctness, we must replicate exactly the offsets used.
            // So we accept the offsets as given: counter at offset +3, encrypted counter at offset +0x23, key schedule at offset +0x43.
            // So we need to copy the IV into the counter field? But the IV copy was into +0xc. That suggests counter field is at +3 and IV field at +0xc.
            // To be safe, we follow the code exactly: after copying IV to ctr+0xc, we call encrypt on ctr+3.
            // The IV in CTR mode is the initial counter value. So perhaps the caller has already placed the counter at ctr+3.
            // The code copies IV into ctr+0xc for later use? 
            // Let's just replicate the assembly as given: it does (*(code*)(cipher_encrypt_table[cipher]))(ctr+3, ctr+0x23, ctr+0x43);
            // We'll preserve that.
            ((int (*)(void*, void*, void*))cipher_encrypt_table[cipher])((char*)ctr + 3, (char*)ctr + 0x23, (char*)ctr + 0x43);
            result = 0;
        }
        return result;
    }
    else {
        return 10;   // CRYPT_INVALID_KEYSIZE
    }
}