// FUNC_NAME: ctr_encrypt
int ctr_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CTR *ctr) {
    unsigned char xorByte;
    unsigned int *puVar3;
    int iVar2;
    char *pcVar4;

    if (pt == NULL) {
        pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar2 = FUN_00b995f7(pcVar4, "pt != NULL", 0x27, "..\\src\\libtomcrypt\\ctr.c");
        _fprintf((FILE *)(iVar2 + 0x40), pcVar4);
    }
    if (ct == NULL) {
        pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar2 = FUN_00b995f7(pcVar4, "ct != NULL", 0x28, "..\\src\\libtomcrypt\\ctr.c");
        _fprintf((FILE *)(iVar2 + 0x40), pcVar4);
    }
    if (ctr == NULL) {
        pcVar4 = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar2 = FUN_00b995f7(pcVar4, "ctr != NULL", 0x29, "..\\src\\libtomcrypt\\ctr.c");
        _fprintf((FILE *)(iVar2 + 0x40), pcVar4);
    }

    if (ctr->cipher > 31 || cipher_descriptor[ctr->cipher] == NULL) {
        return 10; // CRYPT_INVALID_CIPHER
    }
    if (ctr->blocklen < 0 || ctr->blocklen > 128 || ctr->padlen < 0 || ctr->padlen > 128) {
        return 16; // CRYPT_INVALID_ARG
    }

    if (len != 0) {
        do {
            len--;
            if (ctr->padlen == ctr->blocklen) {
                if (ctr->blocklen > 0) {
                    puVar3 = (unsigned int *)((unsigned char *)ctr + 12); // pointer to counter bytes
                    do {
                        *(unsigned char *)puVar3 = *(unsigned char *)puVar3 + 1;
                        if (*(unsigned char *)puVar3 != 0) break;
                        puVar3 = (unsigned int *)((unsigned char *)puVar3 + 1);
                    } while ((int)((unsigned char *)puVar3 - (unsigned char *)ctr) < ctr->blocklen);
                }
                // Encrypt counter to produce pad
                ((void (*)(unsigned char *, unsigned char *, unsigned char *))cipher_descriptor[ctr->cipher].ecb_encrypt)(
                    (unsigned char *)ctr + 12,           // input (counter)
                    (unsigned char *)ctr + 0x23,         // output pad? offset 35
                    (unsigned char *)ctr + 0x43          // key schedule? offset 67
                );
                ctr->padlen = 0;
            }
            xorByte = *pt;
            pt++;
            *ct = *(unsigned char *)(ctr->padlen + 0x8C + (int)ctr) ^ xorByte;
            ctr->padlen++;
            ct++;
        } while (len != 0);
    }
    return 0;
}